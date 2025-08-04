/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:57:40 by angouby           #+#    #+#             */
/*   Updated: 2025/07/30 18:23:10 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_heredocs(t_heredoc *heredocs)
{
	t_heredoc	*curr;
	t_heredoc	*next;

	if (!heredocs)
		return ;
	curr = heredocs;
	while (curr)
	{
		next = curr->next;
		if (curr->fd != -1)
			close(curr->fd);
		free(curr);
		curr = next;
	}
}

void	free_tokens(t_token *tokens)
{
	t_token	*curr;
	t_token	*next;

	if (!tokens)
		return ;
	curr = tokens;
	while (curr)
	{
		next = curr->next;
		free(curr->value);
		free(curr);
		curr = next;
	}
}

void	free_redirs(t_redir *redirs)
{
	t_redir	*curr;
	t_redir	*next;

	if (!redirs)
		return ;
	curr = redirs;
	while (curr)
	{
		next = curr->next;
		free(curr->file);
		free(curr);
		curr = next;
	}
}

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*curr;
	t_cmd	*next;
	int		i;

	curr = cmd;
	while (curr)
	{
		next = curr->next;
		if (curr->av)
		{
			i = 0;
			while (curr->av[i])
				free(curr->av[i++]);
			free(curr->av);
			free(curr->space_flags);
		}
		free_redirs(curr->redirs);
		free_heredocs(curr->hd);
		free(curr);
		curr = next;
	}
}

void	free_tokens_and_cmdlist(t_token *tokens, t_cmd *commands)
{
	free_tokens(tokens);
	free_cmd_list(commands);
}
