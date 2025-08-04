/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angouby <angouby@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:45:57 by angouby           #+#    #+#             */
/*   Updated: 2025/05/09 21:51:15 by angouby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_output_unsigned(unsigned int nbr)
{
	int	count;
	int	temp;

	count = 0;
	if (nbr > 9)
	{
		temp = ft_output_unsigned(nbr / 10);
		if (temp < 0)
			return (-1);
		count += temp;
	}
	temp = ft_output_char((nbr % 10) + '0');
	if (temp < 0)
		return (-1);
	return (count + temp);
}
