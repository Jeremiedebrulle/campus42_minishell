/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:35:07 by jdebrull          #+#    #+#             */
/*   Updated: 2025/07/31 13:06:49 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_quotes(t_token **tokens, char *str, int *i)
{
	if (str[*i] == 34)
		lexer_quoted_str(tokens, str, i, 34);
	else if (str[*i] == 39)
		lexer_quoted_str(tokens, str, i, 39);
}

void	flag_check(t_token **tokens)
{
	t_token	*tmp;

	tmp = (*tokens);
	while (tmp)
	{
		if (tmp->type == WORD
			|| tmp->type == DOLLAR
			|| tmp->type == DOUBLE_STR
			|| tmp->type == SINGLE_STR
			|| tmp->type == RETURN_VAL)
		{
			if (tmp->space_flag && tmp->next
				&& tmp->next->type != WORD
				&& tmp->next->type != DOLLAR
				&& tmp->next->type != DOUBLE_STR
				&& tmp->next->type != SINGLE_STR
				&& tmp->next->type != RETURN_VAL)
				tmp->space_flag = false;
		}
		tmp = tmp->next;
	}
}

int	lexer(char *str, t_token **tokens)
{
	int	i;

	if (has_unclosed_quotes(str) || has_unsupported_char(str))
		return (1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
			lexer_redir(tokens, str, &i);
		else if (str[i] == '|')
		{
			append_token(tokens, new_token("|", PIPE, str, i + 1));
			i++;
		}
		else if (str[i] == '$')
			lexer_dollar(tokens, str, &i);
		else if (str[i] == '"' || str[i] == '\'')
			lexer_quotes(tokens, str, &i);
		else if (ft_isprint(str[i]) && !ft_isspace(str[i]))
			lexer_word(tokens, str, &i);
		else if (ft_isspace(str[i]))
			i++;
	}
	flag_check(tokens);
	return (0);
}
