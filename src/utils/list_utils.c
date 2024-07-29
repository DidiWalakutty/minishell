/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 15:27:34 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/07/04 15:27:34 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	attach_new_node(t_node *head, t_node *og, int node_i, bool empty_node)
{
	t_node	*new;

	new = ft_calloc(1, sizeof(t_node));
	if (node_i == 0)
	{
		new = head->next;
		free(head->str);
		head = new;
		printf("Head: %s\n", head->str);
	}
	else if (empty_node == true && node_i > 0)
	{
		new = head->next;
		free(head->str);
		free(head);
		head = og;
	}
	else if (empty_node == false && node_i > 0)
	{
		free(head->str);
		free(head);
		head = og;
	}
}

t_node	*last_node(t_node *head)
{
	if (head == NULL)
		return (NULL);
	while (head->next != NULL)
		head = head->next;
	return (head);
}