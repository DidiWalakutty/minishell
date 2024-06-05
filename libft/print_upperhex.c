/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_upperhex.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/17 21:52:54 by diwalaku      #+#    #+#                 */
/*   Updated: 2023/10/10 14:36:21 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_upperhex(unsigned int n)
{
	int	length;

	length = 0;
	if (n >= 16)
	{
		length += print_upperhex(n / 16);
		length += print_upperhex(n % 16);
	}
	else
	{
		if (n < 10)
			length += print_char(n + '0');
		else
			length += print_char(n - 10 + 'A');
	}
	return (length);
}
