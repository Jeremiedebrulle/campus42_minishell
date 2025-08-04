/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angouby <angouby@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:01:36 by angouby           #+#    #+#             */
/*   Updated: 2025/07/27 19:07:14 by angouby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_assignment(const char *arg, t_shell *shell)
{
	char	*eq;
	char	*key;
	char	*raw_value;
	char	*clean_value;
	int		result;	

	eq = ft_strchr(arg, '=');
	if (!eq)
		return (1);
	key = ft_strndup(arg, eq - arg);
	if (!is_valid_env_key(key))
	{
		write(2, "export: not a valid identifier\n", 32);
		free(key);
		return (1);
	}
	raw_value = eq + 1;
	clean_value = strip_quotes(raw_value);
	result = set_env_var(&shell->env_list, key, clean_value, 1);
	free(clean_value);
	free(key);
	return (result);
}

static int	handle_split_assignment(char *prev, char *curr, t_shell *shell)
{
	char	*merged;
	int		status;

	merged = ft_strjoin(prev, curr);
	if (!merged)
	{
		write(2, "export: memory allocation error\n", 32);
		return (1);
	}
	status = handle_assignment(merged, shell);
	free(merged);
	return (status);
}

static int	handle_non_assignment(char *arg, t_shell *shell)
{
	t_env	*env;

	if (!is_valid_env_key(arg))
	{
		write(2, "export: not a valid identifier\n", 32);
		return (1);
	}
	env = shell->env_list;
	while (env)
	{
		if (ft_strcmp(env->key, arg) == 0)
		{
			env->exported = 1;
			return (0);
		}
		env = env->next;
	}
	return (0);
}

static int	process_export_arg(char **av, int i, t_shell *shell)
{
	if (is_assignment(av[i]))
	{
		if (handle_assignment(av[i], shell))
			return (1);
	}
	else if (i > 1 && av[i - 1][ft_strlen(av[i - 1]) - 1] == '=')
	{
		if (handle_split_assignment(av[i - 1], av[i], shell))
			return (1);
	}
	else
	{
		if (handle_non_assignment(av[i], shell))
			return (1);
	}
	return (0);
}

int	builtin_export(char **av, t_shell *shell)
{
	int	i;

	i = 1;
	shell->exit_code = 0;
	if (!av[1])
	{
		print_all_exported(shell->env_list);
		return (shell->exit_code);
	}
	while (av[i])
	{
		if (process_export_arg(av, i, shell))
			shell->exit_code = 1;
		i++;
	}
	return (shell->exit_code);
}
