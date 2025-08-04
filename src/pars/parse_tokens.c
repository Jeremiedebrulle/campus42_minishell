/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:31:24 by jdebrull          #+#    #+#             */
/*   Updated: 2025/07/31 12:31:41 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_heredoc_redir(t_shell *shell, t_token *redir, t_cmd *cmd)
{
	t_heredoc	*new_hd;
	int			fd;

	new_hd = malloc(sizeof(t_heredoc));
	if (!new_hd)
		return (1);
	fd = heredoc_process_token(shell, redir);
	if (fd <= 0)
	{
		free(new_hd);
		return (1);
	}
	new_hd->fd = fd;
	new_hd->next = NULL;
	add_heredoc(&cmd->hd, new_hd);
	return (0);
}

int	parse_redir_token(t_shell *shell, t_token **tokens, t_cmd *cmd)
{
	t_token	*redir;
	t_token	*file_token;

	redir = *tokens;
	*tokens = (*tokens)->next;
	file_token = *tokens;
	if (!file_token || !file_token->value)
		return (print_error("syntax", "expected file after redirection"), 1);
	if (redir->type == HEREDOC)
	{
		if (handle_heredoc_redir(shell, redir, cmd))
			return (1);
	}
	else
	{
		if (!add_redir(cmd, redir->type, file_token->value))
			return (1);
	}
	*tokens = (*tokens)->next;
	return (0);
}

int	create_next_pipeline_cmd(t_cmd **curr, t_cmd **next_cmd)
{
	t_cmd	*new_cmd;

	new_cmd = init_commands();
	if (!new_cmd)
		return (1);
	*next_cmd = new_cmd;
	(*curr)->next = new_cmd;
	*curr = new_cmd;
	return (0);
}

int	parse_cmd_token(t_shell *shell, t_token **tokens, t_cmd **cur, t_cmd **next)
{
	t_token	*token;

	token = *tokens;
	if (token->type == WORD || token->type == DOLLAR
		|| token->type == RETURN_VAL || token->type == SINGLE_STR
		|| token->type == DOUBLE_STR)
	{
		if (!add_args((*cur), token))
			return (1);
	}
	else if ((token->type == REDIRECT_IN || token->type == REDIRECT_OUT || \
			token->type == APPEND || token->type == HEREDOC) && token->next)
	{
		if (parse_redir_token(shell, tokens, *cur))
			return (1);
		return (0);
	}
	else if (token->type == PIPE)
	{
		if (create_next_pipeline_cmd(cur, next))
			return (1);
	}
	(*tokens) = (*tokens)->next;
	return (0);
}

t_cmd	*token_to_cmd(t_shell *shell, t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*curr;
	t_cmd	*next_cmd;

	head = NULL;
	curr = NULL;
	next_cmd = NULL;
	while (tokens)
	{
		if (!curr)
		{
			curr = init_commands();
			if (!curr)
				return (NULL);
			head = curr;
		}
		if (parse_cmd_token(shell, &tokens, &curr, &next_cmd))
		{
			free_cmd_list(head);
			if (g_exit_status == 0)
				print_error("cmd_list", "Error during command construction\n");
			return (NULL);
		}
	}
	return (head);
}
