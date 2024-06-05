/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_pointer.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/18 17:30:18 by diwalaku      #+#    #+#                 */
/*   Updated: 2023/10/10 14:36:12 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_pointer(unsigned long ptr)
{
	int	length;

	length = write(1, "0x", 2);
	if (ptr == 0)
		return (length + (write(1, "0", 1)));
	else
		length += print_lowerhex(ptr);
	return (length);
}
