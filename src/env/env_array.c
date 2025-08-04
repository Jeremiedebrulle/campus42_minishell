/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angouby <angouby@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:19:18 by angouby           #+#    #+#             */
/*   Updated: 2025/07/01 16:21:30 by angouby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static int	add_exported_entry(char **arr, size_t *i, t_env *env)
{
	char	*entry;

	if (!env->exported)
		return (0);
	entry = build_env_entry(env->key, env->value);
	if (!entry)
		return (1);
	arr[*i] = entry;
	(*i)++;
	return (0);
}

char	**env_list_to_array(t_env *env)
{
	char	**arr;
	size_t	count;
	size_t	i;

	i = 0;
	count = env_list_count(env);
	arr = malloc((count + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (env)
	{
		if (add_exported_entry(arr, &i, env))
		{
			while (i > 0)
				free(arr[--i]);
			free(arr);
			return (NULL);
		}
		env = env->next;
	}
	arr[i] = (NULL);
	return (arr);
}
