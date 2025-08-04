/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angouby <angouby@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:04:18 by angouby           #+#    #+#             */
/*   Updated: 2025/04/01 15:04:21 by angouby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*dup;

	i = 0;
	dup = (char *)malloc((ft_strlen(src) + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	while (src[i])
	{
		dup[i] = src[i];
		++i;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strndup(const char *src, size_t n)
{
	size_t	i;
	size_t	j;
	char	*dup;

	if (!src)
		return (NULL);
	i = 0;
	while (src[i] && i < n)
		i++;
	dup = (char *)malloc((i + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	j = 0;
	while (j < i)
	{
		dup[j] = src[j];
		j++;
	}
	dup[i] = '\0';
	return (dup);
}
