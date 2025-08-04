/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angouby <angouby@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:13:06 by angouby           #+#    #+#             */
/*   Updated: 2025/05/09 22:10:40 by angouby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_snprintf_loop(char	**str, size_t n, const char *format, va_list args)
{
	int	i;
	int	len;
	int	written;

	i = 0;
	len = 0;
	written = 0;
	while (format[i] && written < (int)(n - 1))
	{
		if (format[i] == '%' && format[i + 1])
		{
			len = ft_handle_format(str, format[++i], args);
			written += len;
		}
		else
		{
			**str = format[i];
			(*str)++;
			written++;
		}
		i++;
	}
	return (written);
}

int	ft_snprintf(char	*str, size_t n, const char *format, ...)
{
	va_list	args;
	int		written;

	va_start(args, format);
	written = ft_snprintf_loop(&str, n, format, args);
	if (n > 0)
		*str = '\0';
	va_end(args);
	return (written);
}
