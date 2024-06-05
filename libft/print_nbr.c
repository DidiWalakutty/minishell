/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_nbr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/16 22:10:17 by diwalaku      #+#    #+#                 */
/*   Updated: 2023/10/10 14:36:07 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_nbr(int n)
{
	int				length;
	unsigned int	nbr;

	length = 0;
	nbr = 0;
	if (n < 0)
	{
		length += print_char('-');
		nbr = (unsigned int)(n * -1);
	}
	else
		nbr = (unsigned int) n;
	if (nbr > 9)
	{
		length += print_nbr(nbr / 10);
		length += print_nbr(nbr % 10);
	}
	else
		length += print_char(nbr + '0');
	return (length);
}
