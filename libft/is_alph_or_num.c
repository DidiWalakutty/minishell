/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_alph_or_num.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: anonymous <anonymous@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/23 22:30:53 by anonymous     #+#    #+#                 */
/*   Updated: 2024/06/23 22:30:53 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_alph_or_num(char c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}