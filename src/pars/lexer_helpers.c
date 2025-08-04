/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:57:16 by jdebrull          #+#    #+#             */
/*   Updated: 2025/07/30 19:56:26 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_redir(t_token **tokens, char *str, int *i)
{
	if (str[*i] == '>' && str[(*i) + 1] == '>')
	{
		append_token(tokens, new_token(">>", APPEND, str, (*i) + 1));
		(*i)++;
	}
	else if (str[*i] == '<' && str[(*i) + 1] == '<')
	{
		append_token(tokens, new_token("<<", HEREDOC, str, (*i) + 1));
		(*i)++;
	}
	else if (str[*i] == '>')
		append_token(tokens, new_token(">", REDIRECT_OUT, str, (*i) + 1));
	else if (str[*i] == '<')
		append_token(tokens, new_token("<", REDIRECT_IN, str, (*i) + 1));
	(*i)++;
}

static int	special_dollar(t_token **tokens, char *str, int *i)
{
	if (str[(*i) + 1] == '?')
	{
		append_token(tokens, new_token("$?", RETURN_VAL, str, (*i) + 2));
		(*i) += 2;
		return (1);
	}
	else if (str[(*i) + 1] == '\0' || str[(*i) + 1] == ' ')
	{
		append_token(tokens, new_token("$", WORD, str, (*i) + 1));
		(*i)++;
		return (1);
	}
	return (0);
}

void	lexer_dollar(t_token **tokens, char *str, int *i)
{
	int		start;
	char	*tmp;

	start = 0;
	if (special_dollar(tokens, str, i))
		return ;
	else if (!ft_isspace(str[(*i) + 1]) && str[(*i) + 1] != '\0')
	{
		start = (*i);
		while (str[*i] && str[*i] != '\0' && !ft_strchr("\"\' ", str[*i]))
			(*i)++;
		if ((*i) > start)
		{
			tmp = ft_substr(str, start, (*i) - start);
			append_token(tokens, new_token(tmp, DOLLAR, str, (*i)));
			free(tmp);
		}
	}
}

void	lexer_quoted_str(t_token **tokens, char *str, int *i, char quote_type)
{
	int			start;
	char		*tmp;
	t_lexicon	type;

	start = ++(*i);
	while (str[*i] && str[*i] != quote_type)
		(*i)++;
	if (str[*i] == quote_type)
	{
		tmp = ft_substr(str, start, (*i) - start);
		if (quote_type == 34)
			type = DOUBLE_STR;
		else
			type = SINGLE_STR;
		append_token(tokens, new_token(tmp, type, str, (*i) + 1));
		free(tmp);
	}
	if (str[*i])
		(*i)++;
}

void	lexer_word(t_token **tokens, char *str, int *i)
{
	int		start;
	char	*tmp;

	start = (*i);
	while (str[*i] && !ft_strchr("<>|\'\" ", str[*i]))
		(*i)++;
	if ((*i) > start)
	{
		tmp = ft_substr(str, start, (*i) - start);
		append_token(tokens, new_token(tmp, WORD, str, (*i)));
		free(tmp);
	}
}
