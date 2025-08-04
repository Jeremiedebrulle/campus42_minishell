/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angouby <angouby@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:01:46 by angouby           #+#    #+#             */
/*   Updated: 2025/07/16 16:01:46 by angouby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(char **av, t_shell *shell)
{
	int	i;

	if (!av || !shell || !shell->env_list)
	{
		shell->exit_code = 1;
		return (1);
	}
	i = 1;
	shell->exit_code = 0;
	while (av[i])
	{
		if (!is_valid_env_key(av[i]))
		{
			print_error("unset", "no valid identifier\n");
			shell->exit_code = 1;
		}
		else
		{
			unset_env_var(&shell->env_list, av[i]);
		}
		i++;
	}
	return (shell->exit_code);
}
