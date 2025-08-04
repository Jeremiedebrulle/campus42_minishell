/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angouby <angouby@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:55:10 by angouby           #+#    #+#             */
/*   Updated: 2025/05/09 21:46:08 by angouby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nbr_elements, size_t element_size)
{
	void	*ptr;

	if (nbr_elements && element_size > SIZE_MAX / nbr_elements)
		return (NULL);
	ptr = malloc(nbr_elements * element_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nbr_elements * element_size);
	return (ptr);
}
