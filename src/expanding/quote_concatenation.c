/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_concatenation.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/04 18:09:07 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/08/22 18:36:35 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	quote_type_present(t_token *node)
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
int	concatenate_quotes(t_token *list)
{
	t_token	*node;
	t_token	*next_token;
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
				next_token = node->next;
				joined = ft_strconcat(node->str, next_token->str);
				free(node->str);
				node->str = joined;
				node->next = next_token->next;
				free(next_token->str);
				free(next_token);
			}
		}
		node = node->next;
	}
	return (0);
}

bool	spaces_present(t_token *node)
{
	while (node)
	{
		if (node->type == SEPARATOR)
			return (true);
		node = node->next;
	}
	return (false);
}

static int	count_tokens(t_token *nodes)
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

int	remove_spaces(t_token *list)
{
	t_token	*head;
	t_token	*to_delete;
	t_token	*before;

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
