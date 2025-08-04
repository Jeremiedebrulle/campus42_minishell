/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:37:04 by angouby           #+#    #+#             */
/*   Updated: 2025/07/31 16:02:54 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdarg.h>
# include <errno.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <signal.h>
# include <limits.h>

extern int	g_exit_status;

/* //STRUCTURES// */

typedef struct s_env
{
	char			*key;
	char			*value;
	bool			exported;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	t_env	*env_list;		// Linked list of env vars
	bool	interactive;	// Is shell running interactively
	char	*user_input;	// Full input line
	int		exit_code;		// Last command's exit status
	int		should_exit;
	bool	is_child;
	pid_t	*pids;
	int		pid_count;
	bool	sigint_newline;
}	t_shell;

typedef enum e_lexicon
{
	WORD,				// Command or argument
	PIPE,				// |
	REDIRECT_IN,		// <
	REDIRECT_OUT,		// >
	APPEND,				// >>
	HEREDOC,			// <<
	SINGLE_STR,			// 'quotes'
	DOUBLE_STR,			// "quotes"
	DOLLAR,				// $VAR
	RETURN_VAL,			// Return value
	END,				// End of input
}	t_lexicon;

typedef struct s_token
{
	t_lexicon			type;
	bool				space_flag;
	char				*value;		//text of the token
	struct s_token		*next;		//chained list
}	t_token;

typedef struct s_heredoc
{
	int					fd;
	struct s_heredoc	*next;
}	t_heredoc;

typedef struct s_redir
{
	t_lexicon			type;		//REDIRECT_IN, REDIRECT_OUT, APPEND
	char				*file;		// Filename or fd
	struct s_redir		*next;
}	t_redir;

typedef struct s_cmd
{
	char			**av;
	bool			*space_flags;
	int				ac;
	t_redir			*redirs;
	t_heredoc		*hd;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_io_state
{
	int		stdin_backup;
	int		stdout_backup;
}	t_io_state;

/* //HELPERS// */

/* utils.c */
void	print_error(const char *prefix, const char *msg);
void	trim_trailing_newline(char *str);
void	free_tab(char **list);
int		count_args(char **av);
void	cleanup_and_exit(t_shell *shell, t_token *tokens, t_cmd *cmds);

/* free_helpers.c */
void	free_heredocs(t_heredoc *heredocs);
void	free_tokens(t_token *tokens);
void	free_redirs(t_redir *redirs);
void	free_cmd_list(t_cmd *cmd);
void	free_tokens_and_cmdlist(t_token *tokens, t_cmd *commands);

/* init_shell.c*/
int		init_shell(t_shell *shell, char **env);
void	cleanup_shell(t_shell *shell);

/* //ENVIRONMENT// */

/* env_list.c */
t_env	*env_list_from_array(char **envp);
size_t	env_list_count(t_env *env);
t_env	*create_minimal_env(void);

/* env_array.c */
char	*get_env_value(t_env *env, const char *key);
char	**env_list_to_array(t_env *env);

/* env_modifier.c */
int		update_env_var(t_env **env, const char *key, const char *value);
int		set_env_var(t_env **env, const char *key, const char *value, bool exp);
int		unset_env_var(t_env **env, const char *key);

/* env_utils.c */
char	*build_env_entry(const char *key, const char *value);
bool	is_valid_env_key(const char *key);
char	*return_value(char *ret, t_shell *shell);
int		return_value_expand(t_shell *shell, char **res, int *i);
int		multiple_dollar_append(t_env *env, char **res, char *input, int *i);
void	single_dollar_append(char *input, char **res, int *i);
void	free_env_list(t_env *env);

/* //EXECUTION// */

/* exec_builtin.c */
int		exec_builtin_cmd(t_cmd *cmd, t_shell *shell);
int		exec_single_builtin(t_cmd *cmd, t_shell *shell, t_io_state *io);
bool	is_builtin(const char *cmd_name);
bool	is_single_builtin(t_cmd *cmd);

/* exec_cmd.c */
void	exec_external_cmd(t_cmd *cmd, t_shell *shell);
void	dispatch_cmd(t_cmd *cmd, t_shell *shell);
int		parse_and_execute(char *input, t_shell *shell);

/* exec_flow.c */
int		run_command_line(char **argv, t_shell *shell);
int		run_noninteractive_input(t_shell *shell);
int		run_interactive_shell(t_shell *shell);

/* exec_utils.c */
char	*read_user_input(void);
void	save_pid(t_shell *shell, pid_t pid);
bool	is_executable(const char *path);
void	handle_child_exit(int status, t_shell *shell);
int		validate_and_parse(t_token **tokens, t_cmd **commands, t_shell *shell);

/* handle_assignments.c */
bool	is_assignment(const char *str);
int		exec_assignment(const char *assignment, t_shell *shell);

/* handle_fds.c */
void	setup_std_fds(t_io_state *io);
bool	save_std_fds(t_io_state *io);
bool	restore_std_fds(t_io_state *io);
void	update_parent_fds(t_cmd *cmd, int *prev_fd, int pipe_fd[2]);

/* handle_heredoc.c */
int		heredoc_process_token(t_shell *shell, t_token *tmp);

/* handle_paths.c */
char	*resolve_cmd_path(const char *cmd, t_shell *shell);

/* handle_pipes.c */
bool	prepare_pipe(t_cmd *cmd, int pipe_fd[2]);
void	execute_child(t_cmd *cmd, t_shell *shell, int prev_fd, int pipe_fd[2]);
void	wait_for_all(t_shell *shell);

/* handle_redirections.c */
bool	apply_redirections(t_cmd *cmd, t_io_state *io);

/* //BUILTINS// */
int		builtin_cd(char **av, t_shell *shell);
int		builtin_echo(t_cmd *cmd, char **av, t_shell *shell);
int		builtin_env(t_env *env);
int		builtin_exit(char **av, t_shell *shell);
int		builtin_export(char **av, t_shell *shell);
int		builtin_pwd(void);
int		builtin_unset(char **av, t_shell *shell);

/* btin_cd_helpers.c */
char	*get_cd_target(char **av, t_shell *shell);
int		update_cd_env(t_shell *shell, char *oldpwd);
char	*get_oldpwd_or_cwd(t_shell *shell);

/* btin_export_helpers.c */
t_env	**build_env_array(t_env *env, size_t count);
void	sort_env_list(t_env **arr, size_t count);
void	print_all_exported(t_env *env);
void	print_exported_var(const char *key, const char *value);
char	*strip_quotes(const char *str);

/* //PARSING// */

/* expand_env.c */
char	*env_extract_dollar(char *input, int *i);
t_token	*token_expand_variables(t_token *tokens, t_shell *shell);
int		env_expand_variable(char *input, t_env *env, char **res, int *i);
void	env_adjust_index(char *input, int *i);
char	*env_expand_string(char *input, t_shell *shell);

/* lexer.c */
int		lexer(char *str, t_token **tokens);
void	lexer_quotes(t_token **tokens, char *str, int *i);

/* lexer_helpers.c */
void	lexer_redir(t_token **tokens, char *str, int *i);
void	lexer_dollar(t_token **tokens, char *str, int *i);
void	lexer_quoted_str(t_token **tokens, char *str, int *i, char quote_type);
void	lexer_word(t_token **tokens, char *str, int *i);

/* parse_checks.c */
bool	has_unclosed_quotes(char *str);
bool	has_unsupported_char(char *str);

/* parse_cmd_list.c */
t_cmd	*init_commands(void);
int		add_args(t_cmd *cmd, t_token *token);
int		add_redir(t_cmd *cmd, t_lexicon type, char *file);
void	add_heredoc(t_heredoc **hd_list, t_heredoc *new);

/* parse_helpers.c */
char	*env_lookup_var(char *str, t_env *env_list);
char	*char_to_string(char c);
int		len_special_char(char *str);
t_token	*new_token(char *value, t_lexicon type, char *str, int i);
void	append_token(t_token **head, t_token *new);

/* parse_tokens.c */
int		handle_redirection(t_token **tokens, t_cmd *cmd);
t_cmd	*token_to_cmd(t_shell *shell, t_token *tokens);

/* parse_syntax.c */
bool	valid_syntax(t_token *tokens);

/* signals.c */
void	signal_setup(int mode);

#endif
