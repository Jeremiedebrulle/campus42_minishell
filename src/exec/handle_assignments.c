/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_assignments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angouby <angouby@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:22:51 by angouby           #+#    #+#             */
/*   Updated: 2025/07/28 17:23:11 by angouby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_assignment(const char *str)
{
	size_t	i;

	i = 0;
	if (!str || !str[0])
		return (false);
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (false);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	if (str[i] != '=' || i == 0)
		return (false);
	return (true);
}

int	exec_assignment(const char *assignment, t_shell *shell)
{
	char	*equal_sign;
	char	*var;
	char	*value;
	int		ret;

	equal_sign = strchr(assignment, '=');
	if (!equal_sign)
		return (1);
	var = ft_strndup(assignment, equal_sign - assignment);
	value = ft_strdup(equal_sign + 1);
	if (!var || !value)
	{
		free(value);
		free(var);
		return (1);
	}
	ret = set_env_var(&shell->env_list, var, value, false);
	free(var);
	free(value);
	return (ret);
}
