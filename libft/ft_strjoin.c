/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/16 15:43:11 by diwalaku      #+#    #+#                 */
/*   Updated: 2022/11/29 15:03:57 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	x;
	size_t	y;
	int		totallen;
	char	*new;

	x = 0;
	y = 0;
	totallen = ft_strlen(s1) + ft_strlen(s2);
	new = (char *)malloc(sizeof(char) * totallen + 1);
	if (!new)
		return (0);
	while (s1 && x < ft_strlen(s1))
	{
		new[x] = s1[x];
		x++;
	}
	while (s2 && y < ft_strlen(s2))
	{
		new[x + y] = s2[y];
		y++;
	}
	new[x + y] = '\0';
	return (new);
}
