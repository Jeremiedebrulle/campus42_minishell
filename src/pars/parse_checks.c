/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:30:24 by jdebrull          #+#    #+#             */
/*   Updated: 2025/07/24 12:36:07 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	has_unclosed_quotes(char *str)
{
	char	quote;

	quote = 0;
	while (*str)
	{
		if (!quote && (*str == '"' || *str == '\''))
			quote = *str;
		else if (quote && *str == quote)
			quote = 0;
		str++;
	}
	if (quote != 0)
	{
		printf("Open quote %c was not closed.\n", quote);
		return (true);
	}
	return (false);
}

bool	has_unsupported_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			while (str[++i] != '"')
				;
		else if (str[i] == '\'')
			while (str[++i] != '\'')
				;
		else if (str[i] == '\\' || str[i] == ';')
		{
			return (printf("character \\ and ; not handled.\n"), true);
		}
		i++;
	}
	return (false);
}
