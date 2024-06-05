/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_str.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/16 21:54:07 by diwalaku      #+#    #+#                 */
/*   Updated: 2023/10/10 14:36:14 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_str(char *s)
{
	int	length;

	length = 0;
	if (!s)
		return (write(1, "(null)", 6));
	while (s[length])
	{
		print_char(s[length]);
		length++;
	}
	return (length);
}
