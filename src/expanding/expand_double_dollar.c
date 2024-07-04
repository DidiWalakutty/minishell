/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_double_dollar.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 15:27:10 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/07/04 15:27:10 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_double_dollar(t_node *node, bool is_expandable)
{
	int	i;

	i = 0;
	if (is_expandable == false || (node->type != WORD && \
		node->type != DOUBLE_QUOTE))
		return (false);
	i = find_dollar_position(node->str);
	if (node->str[i + 1] == '$')
		return (true);
	return (false);
}

void	set_pid(t_node *node, char **env, t_expand *var)
{
	
}