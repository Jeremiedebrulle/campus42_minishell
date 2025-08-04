/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_flow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:32:22 by angouby           #+#    #+#             */
/*   Updated: 2025/07/28 17:56:14 by angouby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_command_line(char **argv, t_shell *shell)
{
	char	*command_line;
	int		status;

	if (!argv[2])
	{
		shell->exit_code = 1;
		return (1);
	}
	command_line = argv[2];
	status = parse_and_execute(command_line, shell);
	shell->exit_code = status;
	return (status);
}

int	run_noninteractive_input(t_shell *shell)
{
	char	*input_line;

	shell->exit_code = 0;
	input_line = read_user_input();
	while (input_line)
	{
		trim_trailing_newline(input_line);
		shell->exit_code = parse_and_execute(input_line, shell);
		free(input_line);
		input_line = read_user_input();
	}
	return (shell->exit_code);
}

int	run_interactive_shell(t_shell *shell)
{
	int	status;

	status = 0;
	while (1)
	{
		shell->user_input = read_user_input();
		if (!shell->user_input)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		if (*shell->user_input)
		{
			trim_trailing_newline(shell->user_input);
			status = parse_and_execute(shell->user_input, shell);
		}
		free(shell->user_input);
		shell->user_input = NULL;
		shell->exit_code = status;
	}
	return (status);
}
