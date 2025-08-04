/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 10:54:01 by jdebrull          #+#    #+#             */
/*   Updated: 2025/08/04 14:47:22 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc_read_input(t_shell *shell, char *delimiter, int write_fd)
{
	char	*input;

	signal_setup(3);
	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			printf("warning: here-document delimited by EOF '%s'\n", delimiter);
			shell->exit_code = 0;
			close(write_fd);
			exit(0);
		}
		if (ft_strlen(delimiter) == ft_strlen(input)
			&& !ft_strncmp(delimiter, input, ft_strlen(delimiter)))
			break ;
		write(write_fd, input, ft_strlen(input));
		write(write_fd, "\n", 1);
		free(input);
	}
	free(input);
	close(write_fd);
	exit(0);
}

static int	heredoc_handle_error(t_shell *shell, int *pipe_fd, int status)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(pipe_fd[0]);
		g_exit_status = 130;
		shell->exit_code = 130;
		return (-1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
	{
		close(pipe_fd[0]);
		g_exit_status = 130;
		shell->exit_code = 130;
		return (-1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		close(pipe_fd[0]);
		g_exit_status = 130;
		shell->exit_code = 130;
		return (-1);
	}
	return (pipe_fd[0]);
}

static int	heredoc_fork_runner(t_shell *shell, t_token *tmp, int write_fd)
{
	if (!tmp->next)
	{
		printf("minishell: syntax error near unexpected token `newline`\n");
		exit(1);
	}
	heredoc_read_input(shell, tmp->next->value, write_fd);
	return (0);
}

static int	heredoc_create_pipe(t_shell *shell, t_token *tmp, int *pipe_fd)
{
	pid_t	pid;
	int		status;

	if (pipe(pipe_fd) == -1)
		return (-1);
	signal_setup(1);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		heredoc_fork_runner(shell, tmp, pipe_fd[1]);
	}
	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	return (heredoc_handle_error(shell, pipe_fd, status));
}

int	heredoc_process_token(t_shell *shell, t_token *tmp)
{
	int		status;
	int		pipe_fd[2];

	status = heredoc_create_pipe(shell, tmp, pipe_fd);
	signal_setup(0);
	return (status);
}
