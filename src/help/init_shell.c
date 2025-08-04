/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:55:38 by angouby           #+#    #+#             */
/*   Updated: 2025/07/29 15:51:54 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	inc_shell_lvl(t_shell *shell)
{
	char	buffer[12];
	char	*lvl_str;
	int		lvl;

	shell->exit_code = 1;
	if (!shell)
		return (shell->exit_code);
	lvl_str = get_env_value(shell->env_list, "SHLVL");
	if (!lvl_str || !ft_isnumeric(lvl_str))
		lvl = 1;
	else
		lvl = ft_atoi(lvl_str) + 1;
	ft_itoa_buffer(lvl, buffer);
	if (set_env_var(&shell->env_list, "SHLVL", buffer, true))
		return (shell->exit_code);
	shell->exit_code = 0;
	return (shell->exit_code);
}

static int	init_pwd(t_shell *shell)
{
	char	cwd[PATH_MAX];

	shell->exit_code = 1;
	if (!shell || !getcwd(cwd, sizeof(cwd)))
		return (shell->exit_code);
	if (!get_env_value(shell->env_list, "PWD"))
		if (set_env_var(&shell->env_list, "PWD", cwd, true))
			return (shell->exit_code);
	if (!get_env_value(shell->env_list, "OLDPWD"))
		if (set_env_var(&shell->env_list, "OLDPWD", "", true))
			return (shell->exit_code);
	shell->exit_code = 0;
	return (0);
}

static int	init_env(t_shell *shell, char **envp)
{
	shell->exit_code = 1;
	if (!shell)
	{
		print_error("init_env", "invalid argument(s)");
		return (shell->exit_code);
	}
	shell->env_list = env_list_from_array(envp);
	if (!shell->env_list)
	{
		shell->env_list = create_minimal_env();
		if (!shell->env_list)
		{
			print_error("init_env", "failed to initialize environment");
			return (shell->exit_code);
		}
	}
	shell->exit_code = 0;
	return (shell->exit_code);
}

int	init_shell(t_shell *shell, char **env)
{
	ft_memset(shell, 0, sizeof(t_shell));
	shell->interactive = isatty(STDIN_FILENO);
	shell->exit_code = 1;
	if (init_env(shell, env))
		return (shell->exit_code);
	if (init_pwd(shell))
		return (shell->exit_code);
	if (inc_shell_lvl(shell))
		return (shell->exit_code);
	shell->exit_code = 0;
	return (shell->exit_code);
}

void	cleanup_shell(t_shell *shell)
{
	if (shell->user_input)
	{
		free(shell->user_input);
		shell->user_input = NULL;
	}
	free_env_list(shell->env_list);
	shell->env_list = NULL;
	shell->exit_code = 0;
	rl_clear_history();
}
