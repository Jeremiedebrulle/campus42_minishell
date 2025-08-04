/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angouby <angouby@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:43:14 by angouby           #+#    #+#             */
/*   Updated: 2025/07/16 14:43:55 by angouby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

int	builtin_cd(char **av, t_shell *shell)
{
	char	*dir;
	char	*oldpwd;

	shell->exit_code = 1;
	if (count_args(av) > 2)
	{
		write(2, "cd: too many arguments\n", 24);
		return (shell->exit_code);
	}
	dir = get_cd_target(av, shell);
	if (!dir)
		return (shell->exit_code);
	oldpwd = get_oldpwd_or_cwd(shell);
	if (!oldpwd)
		return (shell->exit_code);
	if (chdir(dir) != 0)
	{
		perror("cd");
		free(oldpwd);
		return (shell->exit_code);
	}
	if (update_cd_env(shell, oldpwd) != 0)
		return (shell->exit_code);
	shell->exit_code = 0;
	return (shell->exit_code);
}
