/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_concatenation.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/04 18:09:07 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/08/16 18:16:45 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	quote_type_present(t_node *node)
{
	int	i;
	int	quote_num;

	i = 0;
	quote_num = 0;
	while (node)
	{
		if (node->type == SINGLE_QUOTE || node->type == DOUBLE_QUOTE || \
			node->type == WORD)
		{
			if (node->next && (node->next->type == SINGLE_QUOTE || \
				node->next->type == DOUBLE_QUOTE || node->next->type == WORD))
				i++;
		}
		node = node->next;
	}
	if (i > 0)
		return (true);
	return (false);
}

// This function makes sure that things like 4 seperate nodes: 'e'c"h"'o'
// become one node.
int	concatenate_quotes(t_node *list)
{
	t_node	*node;
	t_node	*next_node;
	char	*joined;

	node = list;
	while (node)
	{
		if (node->type == SINGLE_QUOTE || node->type == DOUBLE_QUOTE || \
			node->type == WORD)
		{
			while (node->next && (node->next->type == SINGLE_QUOTE || \
				node->next->type == DOUBLE_QUOTE || node->next->type == WORD))
			{
				next_node = node->next;
				joined = ft_strconcat(node->str, next_node->str);
				free(node->str);
				node->str = joined;
				node->next = next_node->next;
				free(next_node->str);
				free(next_node);
			}
		}
		node = node->next;
	}
	return (0);
}

bool	spaces_present(t_node *node)
{
	while (node)
	{
		if (node->type == SEPARATOR)
			return (true);
		node = node->next;
	}
	return (false);
}

static int	count_nodes(t_node *nodes)
{
	int	i;

	i = 0;
	while (nodes)
	{
		nodes = nodes->next;
		i++;
	}
	return (i);
}

int	remove_spaces(t_node *list)
{
	t_node	*head;
	t_node	*to_delete;
	t_node	*before;

	head = list;
	before = list;
	while (before->type == SEPARATOR)
	{
		to_delete = before;
		before = to_delete->next;
		head = before;
		free_node(to_delete);
	}
	while (before && before->next)
	{
		if (before->next->type == SEPARATOR)
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
