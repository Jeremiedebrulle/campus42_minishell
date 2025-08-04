/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_export_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angouby <angouby@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:54:53 by angouby           #+#    #+#             */
/*   Updated: 2025/07/28 13:55:05 by angouby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	**build_env_array(t_env *env, size_t count)
{
	size_t	i;
	t_env	**arr;

	arr = malloc(sizeof(t_env *) * count);
	if (!arr)
		return (NULL);
	i = 0;
	while (env && i < count)
	{
		arr[i] = env;
		env = env->next;
		i++;
	}
	return (arr);
}

void	sort_env_list(t_env **arr, size_t count)
{
	size_t	i;
	size_t	j;
	t_env	*tmp;

	i = 0;
	while (i < count)
	{
		j = 0;
		while (j + 1 < count)
		{
			if (ft_strcmp(arr[j]->key, arr[j + 1]->key) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_all_exported(t_env *env)
{
	t_env	**arr;
	size_t	count;
	size_t	i;

	count = env_list_count(env);
	arr = build_env_array(env, count);
	if (!arr)
		return ;
	sort_env_list(arr, count);
	i = 0;
	while (i < count)
	{
		print_exported_var(arr[i]->key, arr[i]->value);
		i++;
	}
	free(arr);
}

void	print_exported_var(const char *key, const char *value)
{
	int	has_value;

	printf("declare -x ");
	printf("%s", key);
	has_value = (value != NULL);
	if (has_value)
	{
		printf("=\"");
		printf("%s", value);
		printf("\"");
	}
	printf("\n");
}

char	*strip_quotes(const char *str)
{
	size_t	len;
	char	quote;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len == 0)
		return (ft_strdup(""));
	quote = str[0];
	if ((quote == '"' || quote == '\'') && str[len - 1] == quote)
		return (ft_substr(str, 1, len - 2));
	return (ft_strdup(str));
}
