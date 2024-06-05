/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 19:43:30 by diwalaku      #+#    #+#                 */
/*   Updated: 2022/10/13 22:22:07 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int d)
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)d)
			return ((char *)(s + i));
		i++;
	}
	if ((char)d == s[i])
		return ((char *)(s + i));
	return (0);
}
