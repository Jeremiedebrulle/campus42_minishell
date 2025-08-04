/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angouby <angouby@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:18:53 by angouby           #+#    #+#             */
/*   Updated: 2025/07/01 16:24:44 by angouby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*create_env_node(const char *str)
{
	t_env	*node;
	char	*eq;

	eq = ft_strchr(str, '=');
	if (!eq)
		return (NULL);
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_substr(str, 0, eq - str);
	node->value = ft_strdup(eq + 1);
	if (!node->key || !node->value)
	{
		free(node->key);
		free(node->value);
		free(node);
		return (NULL);
	}
	node->exported = true;
	node->next = (NULL);
	return (node);
}

static void	append_env_node(t_env **head, t_env **tail, t_env *node)
{
	if (!*head)
	{
		*head = node;
		*tail = node;
	}
	else
	{
		(*tail)->next = node;
		*tail = node;
	}
}

t_env	*env_list_from_array(char **envp)
{
	t_env	*head;
	t_env	*tail;
	t_env	*node;
	int		i;

	head = NULL;
	tail = NULL;
	i = 0;
	while (envp && envp[i])
	{
		node = create_env_node(envp[i]);
		if (!node)
		{
			free_env_list(head);
			return (NULL);
		}
		append_env_node(&head, &tail, node);
		i++;
	}
	return (head);
}

size_t	env_list_count(t_env *env)
{
	size_t	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

t_env	*create_minimal_env(void)
{
	t_env	*list;
	char	cwd[PATH_MAX];

	list = NULL;
	if (!getcwd(cwd, sizeof(cwd)))
		ft_strlcpy(cwd, "/", sizeof(cwd));
	set_env_var(&list, "PWD", cwd, true);
	set_env_var(&list, "SHLVL", "1", true);
	set_env_var(&list, "_", "/usr/bin/env", true);
	set_env_var(&list, "PATH", "/usr/bin:/bin", true);
	return (list);
}
