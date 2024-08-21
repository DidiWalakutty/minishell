/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/14 18:36:22 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/08/21 13:19:12 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// info->node_i = 0; // Tracks node position and where to insert expansion
t_expand	*init_info(t_node *list)
{
	t_expand	*info;

	info = malloc(sizeof(t_expand));
	info->head = list;
	info->char_pos = 0;
	info->heredoc_pos = 0;
	info->expandable = false;
	info->prev_type = WORD;
	return (info);
}

// This function searches the whole node and replaces
// where necessary.
// check for heredoc?
	// Remove spaces perhaps just needed when building commands.
	// Also check if it's just one or more spaces.
	// if (spaces_present(info->head) == true)
	// 	remove_spaces(info->head);
void	expand_input(t_data *data, t_node *node, char **env)
{
	t_expand	*info;

	info = init_info(node);
	while (node)
	{
		if (check_null(&node) == true)
			continue ;
		if (is_dollar(node) == true)
			set_dollar(node, env, info);
		if (is_exit_status(node) == true)
			set_exit_status(data, node, info);
		if (is_double_dollar(node) == true)
			set_pid(node, info);
		node = node->next;
	}
	if (quote_type_present(info->head) == true)
		concatenate_quotes(info->head);
	node = info->head;
	free(info);
}
