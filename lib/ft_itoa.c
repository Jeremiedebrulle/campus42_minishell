/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:59:20 by jdebrull          #+#    #+#             */
/*   Updated: 2025/07/29 15:53:12 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	long	j;
	char	*str;

	j = n;
	i = ft_count((long)n);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = 0;
	if (n == 0)
		str[i] = '0';
	if (n < 0)
	{
		str[0] = '-';
		j *= -1;
	}
	while (j > 0)
	{
		str[i] = j % 10 + '0';
		j /= 10;
		i--;
	}
	return (str);
}
/*int	main(void)
{
	//printf("%s\n", ft_itoa(-2147483648));
	printf("%s\n", ft_itoa(9));
	printf("%s\n", ft_itoa(-9));
}*/