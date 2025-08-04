/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angouby <angouby@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:00:51 by angouby           #+#    #+#             */
/*   Updated: 2025/07/09 14:00:58 by angouby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	count_words(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s && *s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static char	*word_dup(const char *s, char c)
{
	size_t	len;
	size_t	i;
	char	*word;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

static void	free_all(char **arr, size_t i)
{
	while (i > 0)
	{
		i--;
		free(arr[i]);
	}
	free(arr);
}

static const char	*skip_chars(const char *s, char c, int skip_delimiters)
{
	if (skip_delimiters)
	{
		while (*s == c)
			s++;
	}
	else
	{
		while (*s && *s != c)
			s++;
	}
	return (s);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	i;

	if (!s)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		s = skip_chars(s, c, 1);
		if (*s == '\0')
			break ;
		result[i] = word_dup(s, c);
		if (!result[i])
		{
			free_all(result, i);
			return (NULL);
		}
		i++;
		s = skip_chars(s, c, 0);
	}
	result[i] = NULL;
	return (result);
}
