/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:09:22 by angouby           #+#    #+#             */
/*   Updated: 2025/07/29 15:52:43 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_itoa_buffer(int n, char *buffer)
{
	int		len;
	long	nb;
	char	temp[12];
	int		i;

	len = 0;
	nb = (long)n;
	i = 0;
	if (nb < 0)
	{
		buffer[len++] = '-';
		nb = -nb;
	}
	if (nb == 0)
		temp[i++] = '0';
	while (nb > 0)
	{
		temp[i++] = (nb % 10) + '0';
		nb = nb / 10;
	}
	while (i--)
		buffer[len++] = temp[i];
	buffer[len] = '\0';
	return (len);
}
