/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:25:09 by jdebrull          #+#    #+#             */
/*   Updated: 2025/07/31 12:27:16 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_expand_variable(char *input, t_env *env, char **res, int *i)
{
	int		var_len;
	char	*key;
	char	*val;
	int		flag;

	flag = 0;
	(*i)++;
	if (input[*i] == '\0')
		flag = 1;
	var_len = len_special_char(&input[*i]);
	key = ft_substr(&input[*i], 0, var_len);
	val = env_lookup_var(key, env);
	if (val && flag == 0)
		(*res) = ft_strjoin_free((*res), val);
	else if (flag == 1)
		(*res) = ft_strjoin_free((*res), "$");
	else if (flag == 0)
		(*res) = ft_strjoin_free((*res), "");
	free(key);
	(*i) += var_len;
	return (1);
}

void	env_adjust_index(char *input, int *i)
{
	int	f;

	f = 0;
	while (input[*i] == '$' && input[(*i)])
	{
		if (f == 0)
			f = 1;
		else if (f == 1)
			f = 0;
		(*i)++;
	}
	if (f == 1)
		(*i)--;
}

char	*env_extract_dollar(char *input, int *i)
{
	char	*str;
	int		start;

	start = *i;
	env_adjust_index(input, i);
	str = malloc(sizeof(char) * ((*i) - start + 1));
	if (!str)
		return (NULL);
	ft_memset(str, '$', (*i) - start);
	str[(*i) - start] = '\0';
	return (str);
}

char	*env_expand_string(char *input, t_shell *shell)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_strdup("");
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1] == '?')
		{
			if (!return_value_expand(shell, &res, &i))
				return (free(res), (NULL));
		}
		else if (input[i] == '$')
		{
			if (!multiple_dollar_append(shell->env_list, &res, input, &i))
				return (free(res), ft_strdup("$"));
		}
		else
			single_dollar_append(input, &res, &i);
	}
	return (res);
}

t_token	*token_expand_variables(t_token *tokens, t_shell *shell)
{
	t_token	*head;
	char	*new_val;

	head = tokens;
	while (tokens)
	{
		if (tokens->type == RETURN_VAL)
			tokens->value = return_value(tokens->value, shell);
		else if (((tokens->type == DOUBLE_STR) || tokens->type == WORD)
			&& ft_strchr(tokens->value, '$'))
		{
			new_val = env_expand_string(tokens->value, shell);
			free(tokens->value);
			tokens->value = new_val;
		}
		else if (tokens->type == DOLLAR && tokens->value[0] == '$')
		{
			new_val = env_expand_string(tokens->value, shell);
			free(tokens->value);
			tokens->value = new_val;
		}
		tokens = tokens->next;
	}
	return (head);
}
