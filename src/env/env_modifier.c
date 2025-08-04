/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_modifier.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angouby <angouby@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:24:56 by angouby           #+#    #+#             */
/*   Updated: 2025/07/01 16:27:11 by angouby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_env_var(t_env **env, const char *key, const char *value)
{
	t_env	*curr;

	if (!env || !key)
		return (1);
	curr = *env;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			free(curr->value);
			curr->value = ft_strdup(value);
			if (!curr->value)
				return (1);
			return (0);
		}
		curr = curr->next;
	}
	return (1);
}

int	set_env_var(t_env **env, const char *key, const char *value, bool exp)
{
	t_env	*new;

	if (!env || !key || !is_valid_env_key(key))
		return (1);
	if (update_env_var(env, key, value) == 0)
		return (0);
	new = malloc(sizeof(t_env));
	if (!new)
		return (1);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	if (!new->key || !new->value)
	{
		free(new->key);
		free(new->value);
		free(new);
		return (1);
	}
	new->next = *env;
	new->exported = exp;
	*env = new;
	return (0);
}

int	unset_env_var(t_env **env, const char *key)
{
	t_env	*curr;
	t_env	*prev;

	if (!env || !*env || !key)
		return (1);
	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return (0);
		}
		prev = curr;
		curr = curr->next;
	}
	return (1);
}
