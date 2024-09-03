/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   ft_index_chr.c                                    :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/02/14 23:16:51 by sreerink      #+#    #+#                 */
/*   Updated: 2024/02/15 01:26:04 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_index_chr(const char *str, char c)
{
	ssize_t	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
