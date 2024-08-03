/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/14 18:36:22 by diwalaku      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2024/08/03 19:01:01 by diwalaku      ########   odam.nl         */
=======
/*   Updated: 2024/08/02 22:46:06 by diwalaku      ########   odam.nl         */
>>>>>>> 1bee439e77fef66667402a88efc312b066b0b21b
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

// Currently keeps seeing the expanded node as the next.
// if we use info->i: // info->node_i++; at to_next_node == true
void	expand_input(t_data *data, t_node *node, char **env)
{
	t_expand	*info;

	info = init_info(node);
	while (node)
	{
		expandable_type(info, node->type);
		if (check_null(&node) == true)
			continue ;
		// if (check_tilde(node) == true)
		// 	set_tilde(node, env, info);
		if (is_dollar(node, info->expandable) == true)
			set_dollar(node, env, info);
		if (is_exit_status(node, info->expandable) == true)
			set_exit_status(data, node, info);
		if (is_double_dollar(node, info->expandable) == true)
			set_pid(node, info);
		node = node->next;
	}
	node = info->head;
	free(info);
}
