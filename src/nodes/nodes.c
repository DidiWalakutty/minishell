/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nodes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 15:28:16 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/07/28 21:56:52 by diwalaku      ########   odam.nl         */
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

// GOES WRONG HERE
void	node_to_list(t_node **head, t_node *new)
{
	t_node	*current_node;

	if (!new)
		return ;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	current_node = last_node(*head);
	current_node->next = new;
	// current_node = new;
	// while (current_node->next != NULL)
	// 	current_node = current_node->next;
	// current_node->next = new;
	// new->previous = current_node;
	// new->next = NULL;
}

// We check for node - 2, because node - 1 will be the current_node.
static void	clear_node(t_node *head, int node_i, bool empty_node)
{
	int		i;
	t_node	*original;
	t_node	*current_node;
	t_node	*previous_node;

	i = 0;
	empty_node = true;
	original = head;
	current_node = NULL;
	previous_node = NULL;
	while (i++ < node_i)
	{
		head = head->next;
		if (i == node_i - 2)
			previous_node = head;
	}
	current_node = head->next;
	previous_node->next = current_node;
	attach_new_node(head, original, node_i, empty_node);
}

// This functions replaces the OG node with the expanded node and 
// places it into the right position of the head (all  nodes).
void	replace_node(t_node *new, t_node *head, int node_i, bool empty_node)
{
	int		i;
	t_node	*old_node;
	t_node	*current_node;
	t_node	*previous_node;

	i = 0;
	old_node = head;
	// current_node = NULL;
	previous_node = head;
	if (new == NULL)
	{
		clear_node(head, node_i, empty_node);
		return ;
	}
	while (i++ < node_i)
	{
		head = head->next;
		if (i == node_i - 1)
			previous_node = head;
	}
	current_node = (head)->next;
	previous_node->next = new;
	while (new->next)
		new = new->next;
	new->next = current_node;
	new->next = NULL;
	attach_new_node(head, old_node, node_i, empty_node);
}
