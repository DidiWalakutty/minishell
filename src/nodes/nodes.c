/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nodes2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/14 18:44:14 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/06/14 18:44:24 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_node(char *str)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->str = str;
	new_node->type = EMPTY;
	new_node->next = NULL;
	new_node->previous = NULL;
	return (new_node);
}

void	node_to_list(t_node **list, t_node *new)
{
	t_node	*current;

	current = *list;
	if (!new)
		return ;
	if (!current)
	{
		*list = new;
		return ;
	}
	while (current->next != NULL)
		current = current->next;
	current->next = new;
	new->previous = current;
	new->next = NULL;
}
