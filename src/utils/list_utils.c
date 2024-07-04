/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/28 15:26:33 by anonymous     #+#    #+#                 */
/*   Updated: 2024/06/28 15:26:33 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_node	*attach_list_token(t_node **head, t_node *new_node)
// {
// 	t_node	*last_node;

// 	if (*head == NULL)
// 	{
// 		*head = new_node;
// 		return ;
// 	}
// 	last_node = *head;
// 	while (last_node->next != NULL)
// 		last_node = last_node->next;
// 	last_node->next = new_node;
// }

int	list_size(t_node *list)
{
	int	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}