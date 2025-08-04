/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angouby <angouby@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:24:42 by angouby           #+#    #+#             */
/*   Updated: 2025/02/06 10:18:07 by angouby          ###   ########.fr       */
/*   Updated: 2025/02/06 09:44:53 by angouby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_append(int fd, char *buffer)
{
	char	temp[BUFFER_SIZE + 1];
	int		bytes_read;

	if (!buffer)
		buffer = ft_strdup("");
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		temp[bytes_read] = '\0';
		buffer = ft_strjoin_free(buffer, temp);
		if (!buffer)
			return (NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (buffer);
}

static char	*extract_line(char *buffer)
{
	char		*line;
	size_t		len;

	if (!buffer || !*buffer)
		return (NULL);
	len = 0;
	while (buffer[len] && buffer[len] != '\n')
		len++;
	if (buffer[len] == '\n')
		len++;
	line = (char *)malloc(len + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, buffer, len);
	line[len] = '\0';
	return (line);
}

static char	*create_new_buffer(char *buffer, size_t len)
{
	char	*new_buffer;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	new_buffer = (char *)malloc(ft_strlen(buffer) - len + 1);
	if (!new_buffer)
		return (free(buffer), NULL);
	while (buffer[len + i])
		new_buffer[j++] = buffer[len + i++];
	new_buffer[j] = '\0';
	free(buffer);
	return (new_buffer);
}

static char	*trim_buffer(char *buffer)
{
	size_t	len;

	len = 0;
	if (!buffer)
		return (NULL);
	while (buffer[len] && buffer[len] != '\n')
		len++;
	if (!buffer[len] || !buffer[len + 1])
		return (free(buffer), NULL);
	return (create_new_buffer(buffer, len + 1));
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_and_append(fd, buffer);
	if (!buffer)
	{
		buffer = NULL;
		return (NULL);
	}
	line = extract_line(buffer);
	if (!line)
		return (free(buffer), buffer = NULL);
	buffer = trim_buffer(buffer);
	return (line);
}
/*
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc != 2)
	{
		printf("Error: Please provide a test file.\n");
		printf("Usage: %s <file>\n", argv[0]);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	printf("Reading: %s\n\n", argv[1]);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
*/
