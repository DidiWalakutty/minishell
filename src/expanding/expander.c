/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diwalaku <diwalaku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:36:22 by diwalaku          #+#    #+#             */
/*   Updated: 2024/07/04 18:56:37 by diwalaku         ###   ########.fr       */
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
	return (info);
}

void	expandable_type(t_expand *info, t_token type)
{
	if (type == HERE_DOC)
		info->expandable = false;
	else
		info->expandable = true;
}

void	expand_input(t_node *list, char **env)
{
	t_expand	*info;

	info = init_info(list);
	while (list)
	{
		// check tilde ~
		expandable_type(info, list->type);
		// if (is_double_dollar(list, info->expendable) == true)
		// 	set_pid(list, env, info);
		if (is_dollar(list, info->expandable) == true)
			set_dollar(list, env, info);
		else
		{
			// needs to iterate, but first check if set_dollar works properly.
			break ;
		}
	}
}
