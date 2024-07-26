/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                           :+:    :+:             */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 17:06:02 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/07/26 16:36:35 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	if_valid_char(char c)
{
	if (is_alph_or_num(c) || c == '_')
		return (1);
	return (0);
}
