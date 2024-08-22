/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/22 18:14:21 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/08/22 19:19:28 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	a_redirection(t_token *node)
{
	if (node->type == REDIR_IN || node->type == REDIR_OUT || \
		node->type == APPEND || node->type == HERE_DOC)
		return (true);
	return (false);
}

// Checks for space-input only and
// pipe_usage.
int	not_just_spaces(t_token *nodes)
{
	int		count;
	bool	flag;
	t_token	*copy;

	count = 0;
	flag = false;
	copy = nodes;
	while (nodes)
	{
		if (nodes->type == SEPARATOR)
			flag = true;
		count++;
		nodes = nodes->next;
	}
	if (flag && count == 1)
		return (0);
	remove_spaces(copy);
	return (1);
}
