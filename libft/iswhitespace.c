/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   iswhitespace.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/28 17:10:44 by diwalaku      #+#    #+#                 */
/*   Updated: 2023/12/08 15:34:01 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	iswhitespace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (true);
	return (false);
}
