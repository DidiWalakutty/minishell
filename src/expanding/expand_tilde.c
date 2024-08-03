/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_tilde.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 18:48:40 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/08/03 18:52:27 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_tilde(t_node *node, bool is_expandable)
{
	if (is_expandable == false || node->type != WORD)
		return (false);
	
}