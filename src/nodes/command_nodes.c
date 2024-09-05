/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_nodes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/05 14:34:42 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/05 18:22:48 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**dup_cmd_args(char **array)
{
	char	**copy;
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (array[size])
		size++;
	copy = malloc(sizeof(char *) * (size + 1));
	if (!copy)
		return (NULL);
	while (array[i])
	{
		copy[i] = ft_strdup(array[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static t_redir_in	*dup_redir_in(t_redir_in *redir)
{
	t_redir_in	*new_list;
	t_redir_in	**tail;
	t_redir_in	*new_node;

	new_list = NULL;
	tail = &new_list;
	new_node = malloc(sizeof(t_redir_in));
	if (!new_node)
		return (NULL);
	while (redir)
	{
		new_node = dup_redir_in_node(redir);
		if (!new_node)
			printf("free all?\n"); // free all nodes?
		*tail = new_node;		// append new_node to the list.
		tail = &new_node->next; // Move tail to point to the new end.
		redir = redir->next;	// Move to the next node in the OG list.
	}
	return (new_list);
}

static t_redir_out	*dup_redir_out(t_redir_out *redir)
{
	t_redir_out	*new_list;
	t_redir_out	**tail;
	t_redir_out	*new_node;

	new_list = NULL;
	tail = &new_list;
	new_node = malloc(sizeof(t_redir_out));
	if (!new_node)
		return (NULL);
	while (redir)
	{
		new_node = dup_redir_out_node(redir);
		if (!new_node)
			printf("free all?\n"); // free all nodes?
		*tail = new_node;
		tail = &new_node->next;
		redir = redir->next;
	}
	return (new_list);
}

t_cmd	*new_cmd_node(t_cmd *command)
{
	t_cmd	*new_node;

	new_node = malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	if (command->command)
		new_node->command = ft_strdup(command->command);
	else
		new_node->command = NULL;
	new_node->args = dup_cmd_args(command->args);
	new_node->redir_in = dup_redir_in(command->redir_in);
	new_node->redir_out = dup_redir_out(command->redir_out);
	new_node->type = command->type; // not needed anymore.
	new_node->next = NULL;
	return (new_node);
}