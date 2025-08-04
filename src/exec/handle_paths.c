/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angouby <angouby@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:09:18 by angouby           #+#    #+#             */
/*   Updated: 2025/07/09 14:51:29 by angouby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

static char	*build_executable_path(const char *dir, const char *cmd)
{
	char	*full_path;
	int		len;

	len = ft_strlen(dir) + ft_strlen(cmd) + 2;
	full_path = malloc(len);
	if (!full_path)
		return (NULL);
	ft_sprintf(full_path, "%s/%s", dir, cmd);
	return (full_path);
}

static char	*find_cmd_recursive(char **paths, const char *cmd, int i)
{
	char	*full_path;

	if (!paths[i])
		return (NULL);
	full_path = build_executable_path(paths[i], cmd);
	if (!full_path)
		return (NULL);
	if (is_executable(full_path))
		return (full_path);
	free(full_path);
	return (find_cmd_recursive(paths, cmd, i + 1));
}

static char	*find_cmd_in_path(const char *cmd, char *path_var)
{
	char	**paths;
	char	*result;

	if (!path_var || !*path_var)
		return (NULL);
	paths = ft_split(path_var, ':');
	if (!paths || !paths[0])
	{
		free_tab(paths);
		return (NULL);
	}
	result = find_cmd_recursive(paths, cmd, 0);
	free_tab(paths);
	return (result);
}

char	*resolve_cmd_path(const char *cmd, t_shell *shell)
{
	char	*path_var;

	if (ft_strchr(cmd, '/'))
	{
		if (is_executable(cmd))
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	path_var = get_env_value(shell->env_list, "PATH");
	if (!path_var)
		return (NULL);
	return (find_cmd_in_path(cmd, path_var));
}
