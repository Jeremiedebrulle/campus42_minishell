/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:22:22 by jdebrull          #+#    #+#             */
/*   Updated: 2025/07/09 15:17:15 by angouby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(const char *prefix, const char *msg)
{
	if (!prefix || !msg)
		return ;
	while (*prefix)
		write(2, prefix++, 1);
	if (prefix && msg)
		write(2, ": ", 2);
	while (*msg)
		write(2, msg++, 1);
	write(2, "\n", 1);
}

void	trim_trailing_newline(char *str)
{
	size_t	len;

	len = strlen(str);
	if (!str)
		return ;
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}

void	free_tab(char **list)
{
	int	i;

	i = 0;
	if (!list)
		return ;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
}

int	count_args(char **av)
{
	int	count;

	count = 0;
	while (av[count])
		count++;
	return (count);
}

void	cleanup_and_exit(t_shell *shell, t_token *tokens, t_cmd *cmds)
{
	rl_clear_history();
	free_tokens_and_cmdlist(tokens, cmds);
	cleanup_shell(shell);
	exit(shell->exit_code);
}
