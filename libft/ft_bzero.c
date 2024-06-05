/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/10 13:47:36 by diwalaku      #+#    #+#                 */
/*   Updated: 2022/11/10 17:55:02 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	x;
	char	*ptr;

	ptr = s;
	x = 0;
	while (x < n)
	{
		*ptr = '\0';
		ptr++;
		x++;
	}
}
