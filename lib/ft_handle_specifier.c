/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_specifier.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angouby <angouby@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:28:41 by angouby           #+#    #+#             */
/*   Updated: 2025/02/04 11:01:25 by angouby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_handle_specifier(const char spec, va_list args)
{
	int	count;

	count = 0;
	if (spec == 'c')
		count = ft_output_char(va_arg(args, int));
	else if (spec == 's')
		count = ft_output_string(va_arg(args, char *));
	else if (spec == 'p')
		count = ft_output_pointer(va_arg(args, void *));
	else if (spec == 'd' || spec == 'i')
		count = ft_output_integer(va_arg(args, int));
	else if (spec == 'u')
		count = ft_output_unsigned(va_arg(args, unsigned int));
	else if (spec == 'x' || spec == 'X')
		count = ft_output_hexa(va_arg(args, unsigned int), (int)spec);
	else if (spec == '%')
		return (write(1, "%", 1));
	else
		return (0);
	if (count < 0)
		return (-1);
	return (count);
}
