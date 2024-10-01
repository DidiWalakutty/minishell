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

	command = malloc(sizeof(t_cmd));
	if (!command)
		return (NULL);
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

static int	of_typ(t_type type)
{
	if (type == WORD || type == DOUBLE_QUOTE || type == SINGLE_QUOTE)
		return (1);
	return (0);
}

static t_token	*remove_empty_words(t_token *list)
{
	t_token	*head;
	t_token	*to_delete;
	t_token	*before;

	head = list;
	before = list;
	while (before && of_typ(before->type) && ft_strcmp(before->str, "") == 0)
	{
		to_delete = before;
		before = to_delete->next;
		head = before;
		free_node(to_delete);
	}
	while (before && before->next)
	{
		if (of_typ(before->next->type) && ft_strcmp(before->next->str, "") == 0)
		{
			to_delete = before->next;
			before->next = to_delete->next;
			free_node(to_delete);
		}
		else
			before = before->next;
	}
	return (head);
}
