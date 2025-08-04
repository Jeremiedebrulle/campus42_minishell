/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:35:29 by angouby           #+#    #+#             */
/*   Updated: 2025/07/31 12:29:02 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(t_cmd *cmd, char **av, t_shell *shell)
{
	size_t	i;
	bool	new_line;

	i = 1;
	new_line = true;
	if (av[i] && ft_strncmp(av[i], "-n", 2) == 0)
	{
		new_line = false;
		i++;
	}
	while (av[i])
	{
		if (ft_strncmp(av[i], "~", 2) == 0 && av[i][1] == '\0')
			ft_printf("%s", get_env_value(shell->env_list, "HOME"));
		else
			write(1, av[i], ft_strlen(av[i]));
		if (cmd->space_flags && cmd->space_flags[i] == true)
			write(1, " ", 1);
		i++;
	}
	if (new_line)
		write (1, "\n", 1);
	return (0);
}
