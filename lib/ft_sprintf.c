/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angouby <angouby@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:04:49 by angouby           #+#    #+#             */
/*   Updated: 2025/05/10 21:01:06 by angouby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sprintf(char *str, const char *format, ...)
{
	va_list	args;
	int		i;
	int		len;
	char	*ptr;

	ptr = str;
	i = 0;
	len = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
			len += ft_handle_format(&ptr, format[++i], args);
		else
		{
			*ptr++ = format[i];
			len++;
		}
		i++;
	}
	*ptr = '\0';
	va_end(args);
	return (len);
}
