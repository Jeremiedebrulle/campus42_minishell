/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angouby <angouby@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:48:47 by angouby           #+#    #+#             */
/*   Updated: 2025/05/09 21:52:05 by angouby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_format_hexa(const char *chars, unsigned int nbr)
{
	int	count;
	int	temp;

	count = 0;
	if (nbr >= 16)
	{
		temp = ft_format_hexa(chars, nbr / 16);
		if (temp < 0)
			return (-1);
		count += temp;
		temp = ft_format_hexa(chars, nbr % 16);
		if (temp < 0)
			return (-1);
		count += temp;
	}
	else
	{
		temp = ft_output_char(chars[nbr]);
		if (temp < 0)
			return (-1);
		count += temp;
	}
	return (count);
}

int	ft_output_hexa(unsigned int nbr, int spec)
{
	const char	*chars;
	int			count;

	if (spec == 'x')
		chars = "0123456789abcdef";
	else if (spec == 'X')
		chars = "0123456789ABCDEF";
	else
		return (-1);
	count = ft_format_hexa(chars, nbr);
	if (count < 0)
		return (-1);
	return (count);
}
