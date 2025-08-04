/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:20:20 by angouby           #+#    #+#             */
/*   Updated: 2025/07/30 18:06:52 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(const char *cmd_name)
{
	if (!cmd_name)
		return (false);
	return (\
			ft_strcmp(cmd_name, "cd") == 0
		|| ft_strcmp(cmd_name, "echo") == 0
		|| ft_strcmp(cmd_name, "env") == 0
		|| ft_strcmp(cmd_name, "exit") == 0
		|| ft_strcmp(cmd_name, "export") == 0
		|| ft_strcmp(cmd_name, "pwd") == 0
		|| ft_strcmp(cmd_name, "unset") == 0);
}

bool	is_single_builtin(t_cmd *cmd)
{
	if (!cmd || cmd->next != NULL)
		return (false);
	if (!cmd->av || !cmd->av[0])
		return (false);
	return (is_builtin(cmd->av[0]));
}

int	exec_single_builtin(t_cmd *cmd, t_shell *shell, t_io_state *io)
{
	if (apply_redirections(cmd, io))
		shell->exit_code = exec_builtin_cmd(cmd, shell);
	restore_std_fds(io);
	return (shell->exit_code);
}

int	exec_builtin_cmd(t_cmd *cmd, t_shell *shell)
{
	if (!cmd->av || !cmd->av[0])
		return (1);
	if (strcmp(cmd->av[0], "cd") == 0)
		return (builtin_cd(cmd->av, shell));
	else if (strcmp(cmd->av[0], "echo") == 0)
		return (builtin_echo(cmd, cmd->av, shell));
	else if (ft_strcmp(cmd->av[0], "env") == 0)
		return (builtin_env(shell->env_list));
	else if (ft_strcmp(cmd->av[0], "exit") == 0)
		return (builtin_exit(cmd->av, shell));
	else if (ft_strcmp(cmd->av[0], "export") == 0)
		return (builtin_export(cmd->av, shell));
	else if (ft_strcmp(cmd->av[0], "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(cmd->av[0], "unset") == 0)
		return (builtin_unset(cmd->av, shell));
	return (1);
}
