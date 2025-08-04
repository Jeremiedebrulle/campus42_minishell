/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:27:32 by jdebrull          #+#    #+#             */
/*   Updated: 2025/07/30 15:28:18 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*return_value(char *ret, t_shell *shell)
{
	if (!shell)
		return (NULL);
	else
	{
		if (ret)
			free(ret);
		return (ft_itoa(shell->exit_code));
	}
}

int	return_value_expand(t_shell *shell, char **res, int *i)
{
	char	*buff;

	buff = NULL;
	buff = return_value(buff, shell);
	if (!buff)
		return (0);
	(*res) = ft_strjoin_free((*res), buff);
	free(buff);
	(*i) += 2;
	return (1);
}

int	multiple_dollar_append(t_env *env, char **res, char *input, int *i)
{
	char	*buff;

	buff = NULL;
	if (input[(*i) + 1] == '$')
	{
		buff = env_extract_dollar(input, i);
		(*res) = ft_strjoin_free((*res), buff);
		free(buff);
	}
	else if (ft_isdigit(input[(*i) + 1]))
		(*i) += 2;
	else if (!env_expand_variable(input, env, res, i))
		return (0);
	return (1);
}

void	single_dollar_append(char *input, char **res, int *i)
{
	char	*buff;

	buff = char_to_string(input[(*i)]);
	(*res) = ft_strjoin_free((*res), buff);
	free(buff);
	(*i)++;
}
