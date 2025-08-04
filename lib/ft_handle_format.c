/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angouby <angouby@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:40:27 by angouby           #+#    #+#             */
/*   Updated: 2025/05/09 21:58:43 by angouby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>

int	ft_itoa(int n, char *buffer);

int	ft_handle_str(char **str, char *s)
{
	int	i;

	i = 0;
	if (!s)
		s = "(null)";
	while (s[i])
	{
		(*str)[i] = s[i];
		i++;
	}
	*str += i;
	return (i);
}

int	ft_handle_int(char **str, int n)
{
	char	tmp[12];
	int		i;
	int		j;

	i = ft_itoa(n, tmp);
	j = 0;
	while (j < i)
	{
		*(*str)++ = tmp[j];
		j++;
	}
	return (i);
}

int	ft_handle_format(char **str, char specifier, va_list args)
{
	if (specifier == 's')
		return (ft_handle_str(str, va_arg(args, char *)));
	if (specifier == 'd' || specifier == 'i')
		return (ft_handle_int(str, va_arg(args, int)));
	if (specifier == 'c')
	{
		**str = (char)va_arg(args, int);
		(*str)++;
		return (1);
	}
	return (0);
}
