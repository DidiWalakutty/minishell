/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build_commands.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/12 17:57:27 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/08/16 20:38:34 by diwalaku      ########   odam.nl         */
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

static bool	correct_pipe_syntax(t_node *nodes, bool *pipe_error, t_data *data)
{
	while (nodes)
	{
		if (nodes->type == PIPE)
		{
			if (*pipe_error)
			{
				// error_exit("Incorrect pipes\n", STDERR_FILENO);
				data->exit_status = 2;
				return (1);
			}
			*pipe_error = true;
		}
		else
			*pipe_error = false;
		nodes = nodes->next;
	}
	return (*pipe_error);
}

static int	correct_pipe_usage(t_node *nodes, t_data *data)
{
	t_node	*head;
	bool	pipe_error;

	head = nodes;
	pipe_error = false;
	if (correct_pipe_syntax(nodes, &pipe_error, data) == false)
		return (1);
	return (0);
}

// Checks for space-input only and
// pipe_usage.
static int	ready_for_building(t_node *nodes, t_data *data, char *input)
{
	int		count;
	bool	flag;
	t_node	*head;

	count = 0;
	flag = false;
	head = nodes;
	while (nodes)
	{
		if (nodes->type == SEPARATOR)
			flag = true;
		count++;
		nodes = nodes->next;
	}
	if (flag && count == 1)
		return (0);
	if (!correct_pipe_usage(head, data))
		return (0);
	return (1);
}

t_cmd	*build_commands(t_node *nodes, t_data *data)
{
	t_cmd	*commands;

	commands = NULL;
	if (nodes && ready_for_building(nodes, data, data->input))
	{
		printf("syntax is alright\n");
	}
	return (commands);
}