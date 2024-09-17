/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build_inits_and_nodes.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/23 15:45:42 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/13 20:28:07 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_redirects(t_cmd *cmd)
{
	cmd->redir_in = NULL;
	cmd->redir_out = NULL;
}

t_cmd	*init_cmds(t_data *data)
{
	t_cmd	*command;

	command = mem_check(malloc(sizeof(t_cmd)));
	command->cmd = NULL;
	command->pid = 0;
	command->path = NULL;
	command->args = NULL;
	command->env = data->env;
	command->redir_in = NULL;
	command->redir_out = NULL;
	command->pipe_in = false;
	command->pipe_out = false;
	command->builtin = NO_BUILTIN;
	command->next = NULL;
	return (command);
}

static int	remove_empty_words(t_token *list)
{
	t_token	*head;
	t_token	*to_delete;
	t_token	*before;

	head = list;
	before = list;
	while (before->type == WORD && ft_strcmp(before->str, "") == 0)
	{
		to_delete = before;
		before = to_delete->next;
		head = before;
		free_node(to_delete);
	}
	while (before && before->next)
	{
		if (before->next->type == WORD && ft_strcmp(before->next->str, "") == 0)
		{
			to_delete = before->next;
			before->next = to_delete->next;
			free_node(to_delete);
		}
		else
			before = before->next;
	}
	return (0);
}

int	empty_words(t_token *nodes)
{
	int		count;
	bool	flag;
	t_token	*copy;

	count = 0;
	flag = false;
	copy = nodes;
	if (!nodes)
		return (0);
	while (nodes)
	{
		if ((nodes->type == WORD || nodes->type == DOUBLE_QUOTE || \
			nodes->type == SINGLE_QUOTE) && ft_strcmp(nodes->str, "") == 0)
			flag = true;
		count++;
		nodes = nodes->next;
	}
	if (flag && count == 1)
		return (0);
	remove_empty_words(copy);
	return (1);
}
