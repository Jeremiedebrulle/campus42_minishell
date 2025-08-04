/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angouby <angouby@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:49:31 by angouby           #+#    #+#             */
/*   Updated: 2025/05/09 21:59:40 by angouby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_format_pointer(uintptr_t	nbr)
{
	const char	*chars;
	int			count;

	count = 0;
	chars = "0123456789abcdef";
	if (nbr >= 16)
		count += ft_format_pointer(nbr / 16);
	if (count < 0)
		return (-1);
	count += ft_output_char(chars[nbr % 16]);
	if (count < 0)
		return (-1);
	return (count);
}

int	ft_output_pointer(void *addr)
{
	int			count;
	uintptr_t	addr_value;

	if (!addr)
		return (ft_output_string("(nil)"));
	count = ft_output_string("0x");
	if (count < 0)
		return (-1);
	addr_value = (uintptr_t)addr;
	count += ft_format_pointer(addr_value);
	if (count < 0)
		return (-1);
	return (count);
}
