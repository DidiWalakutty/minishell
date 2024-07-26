/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 19:05:04 by diwalaku      #+#    #+#                 */
/*   Updated: 2022/11/10 15:04:26 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	h;
	size_t	n;

	h = 0;
	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	while (haystack[h] != '\0' && h < len)
	{
		n = 0;
		while (haystack[h + n] == needle[n] && needle[n] != '\0' && h + n < len)
		{
			n++;
			if (n == ft_strlen(needle))
			{
				return ((char *)&haystack[h]);
			}
		}
		h++;
	}
	return (NULL);
}
