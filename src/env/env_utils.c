/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angouby <angouby@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:27:22 by angouby           #+#    #+#             */
/*   Updated: 2025/07/01 16:28:55 by angouby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*build_env_entry(const char *key, const char *value)
{
	size_t	len;
	char	*str;

	if (!key)
		return (NULL);
	if (!value)
		value = "";
	len = ft_strlen(key) + 1 + ft_strlen(value) + 1;
	str = malloc(len * sizeof(char));
	if (!str)
		return (NULL);
	ft_snprintf(str, len, "%s=%s", key, value);
	return (str);
}

bool	is_valid_env_key(const char *key)
{
	if (!key || !*key || ft_isdigit(*key))
		return (false);
	while (*key)
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (false);
		key++;
	}
	return (true);
}

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}
