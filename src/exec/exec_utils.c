/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:01:45 by angouby           #+#    #+#             */
/*   Updated: 2025/07/31 16:12:44 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

char	*read_user_input(void)
{
	char	*line;

	if (isatty(STDIN_FILENO))
	{
		line = readline("minishell$ ");
		if (line && *line)
			add_history(line);
		return (line);
	}
	else
	{
		line = get_next_line(STDIN_FILENO);
		return (line);
	}
}

void	save_pid(t_shell *shell, pid_t pid)
{
	pid_t	*new_pids;
	int		i;

	new_pids = malloc(sizeof(pid_t) * (shell->pid_count + 1));
	if (!new_pids)
	{
		print_error("save_pid", "malloc failed");
		return ;
	}
	i = 0;
	while (i < shell->pid_count)
	{
		new_pids[i] = shell->pids[i];
		i++;
	}
	new_pids[shell->pid_count] = pid;
	free(shell->pids);
	shell->pids = new_pids;
	shell->pid_count++;
}

bool	is_executable(const char *path)
{
	struct stat	sb;

	return (access(path, X_OK) == 0 && stat(path, &sb) == 0 \
			&& S_ISREG(sb.st_mode));
}

void	handle_child_exit(int status, t_shell *shell)
{
	if (WIFSIGNALED(status))
	{
		shell->exit_code = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT && !shell->sigint_newline)
		{
			write(STDOUT_FILENO, "\n", 1);
			shell->sigint_newline = true;
			shell->exit_code = 130;
		}
		if (WTERMSIG(status) == SIGQUIT && !shell->sigint_newline)
		{
			write(STDOUT_FILENO, "Quit (core dumped)\n", 20);
			shell->sigint_newline = true;
			shell->exit_code = 0;
		}
	}
	else if (WIFEXITED(status))
	{
		shell->exit_code = WEXITSTATUS(status);
	}
	else
		shell->exit_code = 1;
}

int	validate_and_parse(t_token **tokens, t_cmd **commands, t_shell *shell)
{
	*tokens = token_expand_variables(*tokens, shell);
	if (!*tokens || !valid_syntax(*tokens))
		return (1);
	*commands = token_to_cmd(shell, *tokens);
	if (!*commands)
	{
		if (g_exit_status == 130)
			g_exit_status = 0;
		return (1);
	}
	return (0);
}
