/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/10 15:12:21 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/10 15:12:21 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t d)
{
	unsigned int	x;

	x = 0;
	if (d == 0)
	{
		return (0);
	}
	while ((s1[x] == s2[x]) && (x < d - 1) && s1[x])
	{
		x++;
	}
	return ((unsigned char)(s1[x]) - (unsigned char)(s2[x]));
}
