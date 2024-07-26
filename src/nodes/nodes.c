/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nodes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 15:28:16 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/07/26 13:17:49 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_node(char *str, t_token type)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->str = str;
	new_node->type = type;
	new_node->next = NULL;
	new_node->previous = NULL;
	return (new_node);
}

void	node_to_list(t_node **head, t_node *new)
{
	t_node	*current;

	current = *head;
	if (!new)
		return ;
	if (!current)
	{
		*head = new;
		return ;
	}
	while (current->next != NULL)
		current = current->next;
	current->next = new;
	new->previous = current;
	new->next = NULL;
}
