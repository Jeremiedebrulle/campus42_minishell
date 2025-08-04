/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:59:13 by angouby           #+#    #+#             */
/*   Updated: 2025/07/31 16:03:51 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_external_cmd(t_cmd *cmd, t_shell *shell)
{
	char	**envp;
	char	*path;

	envp = env_list_to_array(shell->env_list);
	path = resolve_cmd_path(cmd->av[0], shell);
	if (!path)
	{
		print_error(cmd->av[0], "command not found");
		free_tab(envp);
		exit(127);
	}
	execve(path, cmd->av, envp);
	perror("execve failed");
	free(path);
	free_tab(envp);
	exit(1);
}

static bool	fork_setup(t_cmd *cmd, t_shell *shell, int *prev_fd, int pipe_fd[2])
{
	pid_t	pid;

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	if (!prepare_pipe(cmd, pipe_fd))
		return (false);
	pid = fork();
	if (pid == -1)
		return (print_error("fork", NULL), false);
	if (pid == 0)
	{
		signal_setup(2);
		execute_child(cmd, shell, *prev_fd, pipe_fd);
	}
	update_parent_fds(cmd, prev_fd, pipe_fd);
	save_pid(shell, pid);
	signal_setup(1);
	return (true);
}

static int	execute_cmd_list(t_cmd *cmd, t_shell *shell)
{
	int			prev_fd;
	int			pipe_fd[2];
	t_io_state	io;	

	prev_fd = -1;
	setup_std_fds(&io);
	if (cmd && cmd->ac == 1 && is_assignment(cmd->av[0]) && !cmd->next)
		return (exec_assignment(cmd->av[0], shell));
	if (cmd && is_single_builtin(cmd))
		return (exec_single_builtin(cmd, shell, &io));
	shell->sigint_newline = false;
	while (cmd)
	{
		if (!fork_setup(cmd, shell, &prev_fd, pipe_fd))
		{
			shell->exit_code = 1;
			break ;
		}
		cmd = cmd->next;
	}
	wait_for_all(shell);
	restore_std_fds(&io);
	signal_setup(0);
	return (shell->exit_code);
}

int	parse_and_execute(char *input, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*commands;

	if (!input || ft_strisspace(input) || !shell->env_list)
		return (1);
	tokens = NULL;
	commands = NULL;
	lexer(input, &tokens);
	if (validate_and_parse(&tokens, &commands, shell))
	{
		free_tokens_and_cmdlist(tokens, commands);
		return (1);
	}
	signal_setup(0);
	shell->exit_code = execute_cmd_list(commands, shell);
	if (shell->should_exit)
		cleanup_and_exit(shell, tokens, commands);
	free_tokens_and_cmdlist(tokens, commands);
	return (shell->exit_code);
}
