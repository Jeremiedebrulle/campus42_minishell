/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:31:22 by angouby           #+#    #+#             */
/*   Updated: 2025/07/31 16:02:22 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	prepare_pipe(t_cmd *cmd, int pipe_fd[2])
{
	if (!cmd->next)
		return (true);
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (false);
	}
	return (true);
}

static void	setup_child_io(t_cmd *cmd, int prev_fd, int pipe_fd[2])
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
}

void	execute_child(t_cmd *cmd, t_shell *shell, int prev_fd, int pipe_fd[2])
{
	t_io_state	io;

	shell->is_child = true;
	setup_child_io(cmd, prev_fd, pipe_fd);
	ft_bzero(&io, sizeof(io));
	if (!apply_redirections(cmd, &io))
		exit(1);
	signal_setup(2);
	if (cmd->av && cmd->av[0] && is_builtin(cmd->av[0]))
	{
		shell->exit_code = exec_builtin_cmd(cmd, shell);
		exit(shell->exit_code);
	}
	if (cmd->av && cmd->av[0])
		exec_external_cmd(cmd, shell);
	exit(0);
}

void	wait_for_all(t_shell *shell)
{
	int		status;
	pid_t	pid;

	pid = wait(&status);
	while (pid > 0)
	{
		handle_child_exit(status, shell);
		pid = wait(&status);
	}
	free(shell->pids);
	shell->pids = NULL;
	shell->pid_count = 0;
}
