/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/14 18:36:22 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/07/25 15:15:47 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_expand	*init_info(t_node *list)
{
	t_expand	*info;

	info = malloc(sizeof(t_expand));
	info->head = list;
	info->char_pos = 0;
	info->i = 0;
	info->strlen = ft_strlen(list->str);
	info->expandable = false;
	info->prev_type = WORD;
	info->to_next_node = true;
	return (info);
}

void	expandable_type(t_expand *info, t_token type)
{
	if (type == HERE_DOC)
		info->expandable = false;
	else
		info->expandable = true;
}

void	expand_input(t_node *node, char **env)
{
	t_expand	*info;

	info = init_info(node);
	while (node)
	{
		info->to_next_node = true;
		expandable_type(info, node->type);
		// check tilde ~
		// check double_dollar/PID
		if (is_double_dollar(node, info, info->expandable) == true)
			set_pid(node, info);
		if (is_dollar(node, info->expandable) == true)
			set_dollar(node, env, info);
		if (info->to_next_node == true)
			node = node->next;
	}
	node = info->head;
	free(info);
}
