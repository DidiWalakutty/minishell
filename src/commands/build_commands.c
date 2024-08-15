/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build_commands.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/12 17:57:27 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/08/15 18:29:40 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	a_redirection(t_node *node)
{
	if (node->type == REDIR_IN || node->type == REDIR_OUT || \
		node->type == APPEND || node->type == HERE_DOC)
		return (true);
	return (false);
}

t_cmd	*build_commands(t_node *nodes, t_data *data)
{
	t_cmd	*commands;

	commands = NULL;
	while (nodes)
	{
		if (a_redirection(nodes->type) == true)
		{
			handle_redirections(nodes,)
		}
	}
}