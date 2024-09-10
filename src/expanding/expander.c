/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/14 18:36:22 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/06 15:33:47 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// info->node_i = 0; // Tracks node position and where to insert expansion
t_expand	*init_info(t_token *list)
{
	t_expand	*info;

	info = malloc(sizeof(t_expand));
	info->head = list;
	return (info);
}

static void	skip_heredoc_and_spaces(t_token **node, bool *heredoc)
{
	*heredoc = true;
	*node = (*node)->next;
	while (*node && (*node)->type == SEPARATOR)
		*node = (*node)->next;
}

void	expand_input(t_data *data, t_token *node, char **env)
{
	t_expand	*info;
	bool		heredoc;

	info = init_info(node);
	heredoc = false;
	while (node)
	{
		if (check_null(&node) == true)
			continue ;
		if (node->type == HERE_DOC)
			skip_heredoc_and_spaces(&node, &heredoc);
		if (is_dollar(node, heredoc) == true)
			set_dollar(node, env, info);
		if (is_exit_status(node, heredoc) == true)
			set_exit_status(data, node, info);
		if (is_double_dollar(node, heredoc) == true)
			set_pid(node, info);
		heredoc = false;
		node = node->next;
	}
	if (quote_type_present(info->head) == true)
		concatenate_quotes(info->head);
	node = info->head;
	free(info);
}

