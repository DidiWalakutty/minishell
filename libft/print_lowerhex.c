/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_lowerhex.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/17 18:43:38 by diwalaku      #+#    #+#                 */
/*   Updated: 2023/10/10 14:36:05 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_lowerhex(unsigned long n)
{
	int	length;

	length = 0;
	if (n >= 16)
	{
		length += print_lowerhex(n / 16);
		length += print_lowerhex(n % 16);
	}
	if (n < 16)
	{
		if (n < 10)
			length += print_char(n + '0');
		else
			length += print_char(n - 10 + 'a');
	}
	return (length);
}
