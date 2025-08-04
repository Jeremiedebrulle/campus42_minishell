/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:34:45 by angouby           #+#    #+#             */
/*   Updated: 2025/07/29 15:53:48 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdbool.h>
# include "get_next_line.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

int		ft_atoi(const char *str);
void	*ft_calloc(size_t nbr_elements, size_t element_size);
void	ft_bzero(void *s, size_t length);
int		ft_format_hexa(const char *chars, unsigned int nbr);
int		ft_format_pointer(uintptr_t nbr);
void	ft_free_ptr(char **ptr);
void	ft_free_split(char **arr);
int		ft_handle_format(char **str, char specifier, va_list args);
int		ft_handle_specifier(const char spec, va_list args);
int		ft_isalnum(int c);
int		ft_isalpha(char c);
int		ft_isdigit(int c);
bool	ft_isnumber(const char *str);
bool	ft_isnumeric(char *str);
int		ft_isprint(int c);
int		ft_isspace(int c);
char	*ft_itoa(int n);
int		ft_itoa_buffer(int n, char *buffer);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memset(void *s, int argument, size_t length);
int		ft_output_char(char c);
int		ft_output_hexa(unsigned int nbr, int spec);
int		ft_output_integer(int nbr);
int		ft_output_pointer(void *adr);
int		ft_output_string(char *str);
int		ft_output_unsigned(unsigned int nbr);
int		ft_printf(const char *str, ...);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
int		ft_snprintf(char *str, size_t n, const char *format, ...);
int		ft_sprintf(char *str, const char *format, ...);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *str, int argument);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strdup(const char *src);
char	*ft_strndup(const char *src, size_t n);
int		ft_strisspace(const char *str);
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlcat(char *dest, const char *src, size_t dest_size);
size_t	ft_strlcpy(char *dest, const char *src, size_t destsize);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t size);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*get_next_line(int fd);

#endif
