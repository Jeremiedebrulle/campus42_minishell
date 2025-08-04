/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angouby <angouby@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:01:59 by angouby           #+#    #+#             */
/*   Updated: 2025/07/16 16:01:59 by angouby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_env *env)
{
	char	*entry;

	if (!env)
		return (125);
	while (env)
	{
		if (env->exported && env->value)
		{
			entry = build_env_entry(env->key, env->value);
			if (entry)
			{
				write(1, entry, ft_strlen(entry));
				write(1, "\n", 1);
				free(entry);
			}
		}
		env = env->next;
	}
	return (0);
}
