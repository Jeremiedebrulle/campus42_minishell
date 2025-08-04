/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:11:51 by jdebrull          #+#    #+#             */
/*   Updated: 2025/07/24 13:14:39 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_pipe_syntax(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	if (tmp && tmp->type == PIPE)
		return (printf("syntax error near unexpected token '|'\n"), 1);
	while (tmp && tmp->next)
	{
		if (tmp->type == PIPE && tmp->next->type == PIPE)
			return (printf("syntax error near unexpected token '|'\n"), 1);
		tmp = tmp->next;
	}
	if (tmp && tmp->type == PIPE)
		return (printf("syntax error near unexpected token '|'\n"), 1);
	return (0);
}

static int	check_redir_syntax(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp && tmp->next)
	{
		if (tmp->type == REDIRECT_IN || tmp->type == REDIRECT_OUT)
		{
			if (tmp->next->type == REDIRECT_IN)
				return (printf("syntax error near unexpected token '<'\n"), 1);
			if (tmp->next->type == REDIRECT_OUT)
				return (printf("syntax error near unexpected token '>'\n"), 1);
			if (tmp->next->type == APPEND)
				return (printf("syntax error near unexpected token '>>'\n"), 1);
			if (tmp->next->type == HEREDOC)
				return (printf("syntax error near unexpected token '<<'\n"), 1);
			if (tmp->next->type == PIPE)
				return (printf("syntax error near unexpected token '|'\n"), 1);
		}
		tmp = tmp ->next;
	}
	if (tmp && (tmp->type == REDIRECT_IN || tmp->type == REDIRECT_OUT))
		return (printf("syntax error near unexpected token 'newline'\n"), 1);
	return (0);
}

static int	check_heredoc_syntax(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp && tmp->next)
	{
		if (tmp->type == APPEND || tmp->type == HEREDOC)
		{
			if (tmp->next->type == APPEND)
				return (printf("syntax error near unexpected token '>>'\n"), 1);
			if (tmp->next->type == HEREDOC)
				return (printf("syntax error near unexpected token '<<'\n"), 1);
			if (tmp->next->type == REDIRECT_IN)
				return (printf("syntax error near unexpected token '<'\n"), 1);
			if (tmp->next->type == REDIRECT_OUT)
				return (printf("syntax error near unexpected token '>'\n"), 1);
			if (tmp->next->type == PIPE)
				return (printf("syntax error near unexpected token '|'\n"), 1);
		}
		tmp = tmp->next;
	}
	if (tmp && (tmp->type == APPEND || tmp->type == HEREDOC))
		return (printf("syntax error near unexpected token 'newline'\n"), 1);
	return (0);
}

bool	valid_syntax(t_token *tokens)
{
	if (check_pipe_syntax(tokens))
		return (false);
	if (check_redir_syntax(tokens))
		return (false);
	if (check_heredoc_syntax(tokens))
		return (false);
	if (g_exit_status == 130)
	{
		g_exit_status = 0;
		return (false);
	}
	return (true);
}
