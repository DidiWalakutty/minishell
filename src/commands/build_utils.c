/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/22 18:14:21 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/24 16:38:39 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	add_to_array(char **new_array, char **arguments, char *str)
{
	int	i;

	i = 0;
	if (arguments)
	{
		while (arguments[i])
		{
			new_array[i] = ft_strdup(arguments[i]);
			if (!new_array[i])
				return (0);
			i++;
		}
	}
	if (str)
	{
		new_array[i] = ft_strdup(str);
		if (!new_array[i])
			return (0);
		i++;
	}
	new_array[i] = NULL;
	return (1);
}

char	**add_to_double_array(char **arguments, char *str)
{
	int		size;
	char	**new_array;

	size = 0;
	if (!str && !arguments)
		return (NULL);
	if (!str)
		return (arguments);
	if (arguments)
	{
		while (arguments[size])
			size++;
	}
	new_array = malloc(sizeof(char *) * (size + 2));
	if (!new_array)
		return (NULL);
	if (add_to_array(new_array, arguments, str) == 0)
	{
		free_array(new_array);
		return (NULL);
	}
	if (arguments)
		free_array(arguments);
	return (new_array);
}

int	create_redir_in(t_cmd *cmd, char *result, t_redir_type redir_type, \
					t_type token_type)
{
	t_redin	*new_node;
	t_redin	*current;

	new_node = create_in_node(cmd, result, redir_type, token_type);
	if (!new_node)
		return (1);
	if (!cmd->redir_in)
		cmd->redir_in = new_node;
	else
	{
		current = cmd->redir_in;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
	return (0);
}

int	create_redir_out(t_cmd *cmd, char *result, t_redir_type redir_type)
{
	t_redou	*new_node;
	t_redou	*current;

	new_node = create_out_node(cmd, result, redir_type);
	if (!new_node)
		return (1);
	if (!cmd->redir_out)
		cmd->redir_out = new_node;
	else
	{
		current = cmd->redir_out;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
	return (0);
}
