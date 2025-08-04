/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:35:11 by angouby           #+#    #+#             */
/*   Updated: 2025/07/30 18:26:48 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_open_file(t_redir *r)
{
	if (r->type == REDIRECT_IN || r->type == HEREDOC)
		return (open(r->file, O_RDONLY));
	else if (r->type == REDIRECT_OUT)
		return (open(r->file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else if (r->type == APPEND)
		return (open(r->file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (-1);
}

static int	redir_dup_fd(int fd, t_lexicon type)
{
	int	target;

	if (type == REDIRECT_IN || type == HEREDOC)
		target = STDIN_FILENO;
	else
		target = STDOUT_FILENO;
	return (dup2(fd, target));
}

static int	redir_apply(t_redir *r)
{
	int	fd;

	if (!r || !r->file)
		return (1);
	fd = redir_open_file(r);
	if (fd == -1)
	{
		print_error(r->file, strerror(errno));
		return (1);
	}
	if (redir_dup_fd(fd, r->type) == -1)
	{
		print_error("dup2", "Failed to redirect");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static bool	apply_heredoc_fd(t_cmd *cmd, t_io_state *io)
{
	if (!cmd || !save_std_fds(io))
		return (false);
	if (cmd->hd && cmd->hd->fd != -1)
	{
		if (dup2(cmd->hd->fd, STDIN_FILENO) == -1)
		{
			restore_std_fds(io);
			print_error("heredoc dup2", NULL);
			return (false);
		}
		close(cmd->hd->fd);
	}
	return (true);
}

bool	apply_redirections(t_cmd *cmd, t_io_state *io)
{
	t_redir	*r;

	if (!cmd || (!cmd->hd && !cmd->redirs))
		return (true);
	if (!apply_heredoc_fd(cmd, io))
		return (false);
	r = cmd->redirs;
	while (r)
	{
		if (redir_apply(r))
		{
			restore_std_fds(io);
			return (false);
		}
		r = r->next;
	}
	return (true);
}
