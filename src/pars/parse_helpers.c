/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:22:22 by jdebrull          #+#    #+#             */
/*   Updated: 2025/07/30 20:19:02 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_lookup_var(char *str, t_env *env_list)
{
	int		len;
	char	*key;
	char	*value;

	len = len_special_char(str);
	key = ft_substr(str, 0, len);
	if (!key)
		return (NULL);
	value = get_env_value(env_list, key);
	free(key);
	return (value);
}

char	*char_to_string(char c)
{
	char	*buff;

	buff = malloc(2);
	if (!buff)
		return (NULL);
	buff[0] = c;
	buff[1] = '\0';
	return (buff);
}

int	len_special_char(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == 95))
		i++;
	return (i);
}

t_token	*new_token(char *value, t_lexicon type, char *str, int i)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	if (str[i] && str[i] == ' ')
		token->space_flag = true;
	else
		token->space_flag = false;
	token->value = ft_strdup(value);
	token->next = NULL;
	return (token);
}

void	append_token(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
