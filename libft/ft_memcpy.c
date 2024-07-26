/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/10 14:58:07 by diwalaku      #+#    #+#                 */
/*   Updated: 2022/11/10 19:07:53 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*d;
	char	*s;
	size_t	x;

	x = 0;
	d = (char *)dst;
	s = (char *)src;
	if (!dst && !src)
		return (0);
	while (x < n)
	{
		d[x] = s[x];
		x++;
	}
	return (dst);
}
