/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_uns_dec.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/17 18:04:39 by diwalaku      #+#    #+#                 */
/*   Updated: 2023/10/10 14:36:17 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_uns_dec(unsigned int n)
{
	int	length;

	length = 0;
	if (n >= 10)
	{
		length += print_nbr(n / 10);
		length += print_nbr(n % 10);
	}
	if (n < 10)
		length += print_char (n + '0');
	return (length);
}
