/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nodes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 15:28:16 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/08/02 21:10:42 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_node(char *str, t_token type)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	if (str)
		new_node->str = str;
	else
		new_node->str = ft_strdup("");
	new_node->type = type;
	new_node->next = NULL;
	new_node->previous = NULL;
	new_node->null = false;
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
}
