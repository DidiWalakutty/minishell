/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/14 18:36:22 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/08/12 22:00:04 by diwalaku      ########   odam.nl         */
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

static void	expandable_type(t_expand *info, t_token type)
{
	if (type == HERE_DOC)
		info->expandable = false;
	else
		info->expandable = true;
}

// This function searches the whole node and replaces
// where necessary.
// if (check_tilde(node) == true)
// 	set_tilde(node, env, info);
void	expand_input(t_data *data, t_node *node, char **env)
{
	t_expand	*info;

	info = init_info(node);
	while (node)
	{
		expandable_type(info, node->type);
		if (check_null(&node) == true)
			continue ;
		if (is_heredoc(node) == true)
			skip_argument
		if (is_dollar(node, info->expandable) == true)
			set_dollar(node, env, info);
		if (is_exit_status(node, info->expandable) == true)
			set_exit_status(data, node, info);
		if (is_double_dollar(node, info->expandable) == true)
			set_pid(node, info);
		node = node->next;
	}
	if (quote_type_present(info->head) == true)
		concatenate_quotes(info->head);
	if (spaces_present(info->head) == true)
		remove_spaces(info->head);
	node = info->head;
	// free_list(info->head);
	free(info);
}
