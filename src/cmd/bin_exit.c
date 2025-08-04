/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angouby <angouby@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:02:11 by angouby           #+#    #+#             */
/*   Updated: 2025/07/16 16:02:11 by angouby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ctype.h>

static int	parse_exit_code(char **av, t_shell *shell, int *code)
{
	int	num;

	if (!ft_isnumber(av[1]))
	{
		print_error("exit", "numeric argument required\n");
		shell->exit_code = 255;
		return (-2);
	}
	if (av[2])
	{
		print_error("exit", "too many arguments\n");
		shell->exit_code = 1;
		return (-1);
	}
	num = ft_atoi(av[1]) % 256;
	if (num < 0)
		num += 256;
	*code = num;
	return (0);
}

int	builtin_exit(char **av, t_shell *shell)
{
	int	exit_code;
	int	ret;

	if (!shell->is_child)
		write(STDERR_FILENO, "exit\n", 5);
	if (av[1])
	{
		ret = parse_exit_code(av, shell, &exit_code);
		if (ret == -1)
			return (shell->exit_code);
		if (ret == -2)
		{
			shell->exit_code = 255;
			shell->should_exit = true;
			return (255);
		}
	}
	else
		exit_code = shell->exit_code;
	shell->exit_code = exit_code;
	shell->should_exit = true;
	return (exit_code);
}
