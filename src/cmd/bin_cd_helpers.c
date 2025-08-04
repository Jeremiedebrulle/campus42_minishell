/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cd_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angouby <angouby@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:30:28 by angouby           #+#    #+#             */
/*   Updated: 2025/07/30 18:30:28 by angouby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

static char	*get_home_dir(t_shell *shell)
{
	char	*dir;

	dir = get_env_value(shell->env_list, "HOME");
	if (!dir)
	{
		write(2, "cd: HOME not set\n", 18);
		shell->exit_code = 1;
		return (NULL);
	}
	if (dir[0] == '\0')
	{
		shell->exit_code = 0;
		return (NULL);
	}
	return (dir);
}

static char	*get_oldpwd_dir(t_shell *shell)
{
	char	*dir;

	dir = get_env_value(shell->env_list, "OLDPWD");
	if (!dir)
	{
		write(2, "cd: OLDPWD not set\n", 20);
		shell->exit_code = 1;
		return (NULL);
	}
	write(1, dir, ft_strlen(dir));
	write(1, "\n", 1);
	return (dir);
}

char	*get_cd_target(char **av, t_shell *shell)
{
	char	*dir;

	dir = NULL;
	if (!av[1])
		dir = get_home_dir(shell);
	else if (av[1][0] == '-' && av[1][1] == '\0')
		dir = get_oldpwd_dir(shell);
	else if (av[1][0] == '\0')
	{
		write(2, "cd: empty path\n", 16);
		shell->exit_code = 1;
		return (NULL);
	}
	else
		dir = av[1];
	return (dir);
}

int	update_cd_env(t_shell *shell, char *oldpwd)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		cwd = ft_strdup(get_env_value(shell->env_list, "PWD"));
		if (!cwd)
		{
			free(oldpwd);
			return (1);
		}
	}
	update_env_var(&shell->env_list, "OLDPWD", oldpwd);
	update_env_var(&shell->env_list, "PWD", cwd);
	free(oldpwd);
	free(cwd);
	return (0);
}

char	*get_oldpwd_or_cwd(t_shell *shell)
{
	char		*cwd;
	const char	*pwd_env;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		pwd_env = get_env_value(shell->env_list, "PWD");
		if (!pwd_env)
			return (NULL);
		cwd = ft_strdup(pwd_env);
	}
	return (cwd);
}
