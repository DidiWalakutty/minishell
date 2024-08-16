/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build_commands.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/12 17:57:27 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/08/16 20:58:39 by diwalaku      ########   odam.nl         */
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

// Checks for space-input only and
// pipe_usage.
static int	not_just_spaces(t_node *nodes)
{
	int		count;
	bool	flag;

	count = 0;
	flag = false;
	while (nodes)
	{
		if (nodes->type == SEPARATOR)
			flag = true;
		count++;
		nodes = nodes->next;
	}
	if (flag && count == 1)
		return (0);
	return (1);
}

t_cmd	merge_commands(t_node *nodes, t_data *data)
{
	
}

t_cmd	*build_commands(t_node *nodes, t_data *data)
{
	t_cmd	*commands;

	commands = NULL;
	if (nodes && not_just_spaces(nodes))
	{
		commands = merge_commands(nodes, data);
		printf("syntax is alright\n");
	}
	return (commands);
}