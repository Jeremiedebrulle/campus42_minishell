/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angouby <angouby@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:26:52 by angouby           #+#    #+#             */
/*   Updated: 2025/05/09 21:40:10 by angouby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *str, ...)
{
	size_t	i;
	int		count;
	va_list	args;

	if (!str)
		return (-1);
	va_start(args, str);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str [i] == '%')
		{
			i++;
			count += ft_handle_specifier(str[i], args);
		}
		else
			count += ft_output_char(str[i]);
		if (count < 0)
			return (va_end(args), -1);
		i++;
	}
	va_end(args);
	return (count);
}
