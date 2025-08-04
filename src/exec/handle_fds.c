/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angouby <angouby@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:28:14 by angouby           #+#    #+#             */
/*   Updated: 2025/07/23 15:28:27 by angouby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_std_fds(t_io_state *io)
{
	ft_bzero(io, sizeof(*io));
	io->stdin_backup = -1;
	io->stdout_backup = -1;
	save_std_fds(io);
}

bool	save_std_fds(t_io_state *io)
{
	if (!io)
		return (false);
	io->stdin_backup = dup(STDIN_FILENO);
	io->stdout_backup = dup(STDOUT_FILENO);
	return (io->stdin_backup != -1 && io->stdout_backup != -1);
}

bool	restore_std_fds(t_io_state *io)
{
	bool	success;

	success = true;
	if (io->stdin_backup >= 0)
	{
		if (dup2(io->stdin_backup, STDIN_FILENO) == -1)
			success = false;
		else
		{
			close(io->stdin_backup);
			io->stdin_backup = -1;
		}
	}
	if (io->stdout_backup >= 0)
	{
		if (dup2(io->stdout_backup, STDOUT_FILENO) == -1)
			success = false;
		else
		{
			close(io->stdout_backup);
			io->stdout_backup = -1;
		}
	}
	return (success);
}

void	update_parent_fds(t_cmd *cmd, int *prev_fd, int pipe_fd[2])
{
	if (*prev_fd != -1)
	{
		close(*prev_fd);
		*prev_fd = -1;
	}
	if (cmd->next)
	{
		if (pipe_fd[1] != -1)
		{
			close(pipe_fd[1]);
			pipe_fd[1] = -1;
		}
		*prev_fd = pipe_fd[0];
		pipe_fd[0] = -1;
	}
	else if (pipe_fd[0] != -1)
	{
		close(pipe_fd[0]);
		pipe_fd[0] = -1;
	}
}
