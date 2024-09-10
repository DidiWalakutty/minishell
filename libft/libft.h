/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 18:27:25 by diwalaku      #+#    #+#                 */
/*   Updated: 2023/12/08 15:33:50 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdarg.h>
# include <stdbool.h>
# include "../includes/minishell.h"

// libft
size_t	ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
char	*ft_strndup(const char *s1, int len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *str, char c);
char	*ft_strchr(const char *s, int d);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t d);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
bool	iswhitespace(char c);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		is_alph_or_num(char c);
char	*ft_strconcat(char *s1, char *s2);
char	*ft_itoa(int i);
void	*ft_memcpy(void *dst, const void *src, size_t n);

// printf
int		ft_printf(const char *format, ...);
int		print_char(char c);
int		print_str(char *s);
int		print_nbr(int n);
int		print_uns_dec(unsigned int n);
int		print_lowerhex(unsigned long n);
int		print_upperhex(unsigned int n);
int		print_pointer(unsigned long ptr);

#endif