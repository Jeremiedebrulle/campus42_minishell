/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:30:15 by angouby           #+#    #+#             */
/*   Updated: 2025/07/24 17:00:26 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	int		exit_status;

	exit_status = init_shell(&shell, envp);
	if (exit_status != 0)
	{
		print_error("minishell", "Initialization failed");
		return (exit_status);
	}
	if (argc >= 3 && ft_strcmp(argv[1], "-c") == 0)
		exit_status = run_command_line(argv, &shell);
	else if (!isatty(STDIN_FILENO))
	{
		signal_setup(1);
		exit_status = run_noninteractive_input(&shell);
	}
	else
	{
		signal_setup(0);
		exit_status = run_interactive_shell(&shell);
	}
	cleanup_shell(&shell);
	return (exit_status);
}
