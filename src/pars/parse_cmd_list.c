/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:10:00 by jdebrull          #+#    #+#             */
/*   Updated: 2025/07/31 11:34:39 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_commands(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	ft_bzero(cmd, sizeof(t_cmd));
	return (cmd);
}

int	add_args(t_cmd *cmd, t_token *token)
{
	int		i;
	char	**new_av;
	bool	*new_flags;

	i = -1;
	new_av = malloc(sizeof(char *) * (cmd->ac + 2));
	new_flags = malloc(sizeof(bool) * (cmd->ac + 1));
	if (!new_av || !new_flags)
		return (0);
	while (++i < cmd->ac)
	{
		new_av[i] = cmd->av[i];
		new_flags[i] = cmd->space_flags[i];
	}
	new_av[cmd->ac] = ft_strdup(token->value);
	new_flags[cmd->ac] = token->space_flag;
	new_av[cmd->ac + 1] = NULL;
	if (cmd->av)
		free(cmd->av);
	if (cmd->space_flags)
		free(cmd->space_flags);
	cmd->av = new_av;
	cmd->space_flags = new_flags;
	cmd->ac++;
	return (1);
}

int	add_redir(t_cmd *cmd, t_lexicon type, char *file)
{
	t_redir	*new;
	t_redir	*tmp;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (0);
	new->type = type;
	new->file = ft_strdup(file);
	new->next = NULL;
	if (!new->file)
	{
		free(new);
		return (0);
	}
	if (!cmd->redirs)
		cmd->redirs = new;
	else
	{
		tmp = cmd->redirs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (1);
}

void	add_heredoc(t_heredoc **hd_list, t_heredoc *new)
{
	new->next = *hd_list;
	*hd_list = new;
}
