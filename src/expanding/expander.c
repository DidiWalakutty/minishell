/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/14 18:36:22 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/07/23 00:47:01 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_expand	*init_info(t_node *list)
{
	t_expand	*info;

	info = malloc(sizeof(t_expand));
	info->head = list;
	info->i = 0;
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
	//
	//
	// HERE!
	// Won't continu when there's a remainder
	// "Hi $USER hoi" will continuously loop and not pick up the "hoi".
	// Is the problem in expand_input or set_dollar?
	//
	//
	t_expand	*info;

	info = init_info(node);
	while (node)
	{
		printf("still in node: %s\n", node->str);
		// check tilde ~
		// printf("node in while loop is: %s\n", node->str);
		expandable_type(info, node->type);
		// if (is_double_dollar(node, info->expendable) == true)
		// 	set_pid(node, env, info);
		if (is_dollar(node, info->expandable) == true)
		{
			set_dollar(node, env, info);
			if (info->to_next_node == false)
				printf("There's a remainder, to_next_node is false\n");
		}
		if (info->to_next_node == true)
		{
			printf("we can go to the next node\n");
			node = node->next;
			// info->i++;
		}
	}
	node = info->head;
	free(info);
}
