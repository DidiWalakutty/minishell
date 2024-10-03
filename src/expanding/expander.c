/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/14 18:36:22 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/10/03 17:19:18 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_expand	*init_info(t_token *list)
{
	t_expand	*info;

	info = malloc(sizeof(t_expand));
	if (!info)
		return (NULL);
	info->head = list;
	info->mal_fail = false;
	return (info);
}

static void	skip_heredoc_and_spaces(t_token **node, bool *heredoc)
{
	*heredoc = true;
	*node = (*node)->next;
	while (*node && (*node)->type == SEPARATOR)
		*node = (*node)->next;
}

static int	node_expansion(t_token *node, t_expand *info, t_data *data)
{
	bool		heredoc;

	heredoc = false;
	while (node)
	{
		if (check_null(&node) == true)
			continue ;
		if (node->type == HERE_DOC)
			skip_heredoc_and_spaces(&node, &heredoc);
		if (is_dollar(node, heredoc) == true)
			set_dollar(node, data->env, info);
		if (is_double_dollar(node, heredoc) == true)
			set_pid(node, info);
		if (is_exit_status(node, heredoc) == true)
			set_exit_status(data, node, info);
		heredoc = false;
		if (info->mal_fail == true)
			return (-1);
		node = node->next;
	}
	return (0);
}

int	expand_input(t_data *data, t_token **node)
{
	t_expand	*info;

	info = init_info(*node);
	if (!info)
		return (-1);
	if (node_expansion(*node, info, data) == -1)
	{
		free(info);
		return (-1);
	}
	if (quote_type_present(info->head) == true)
	{
		if (concatenate_quotes(info->head) == -1)
		{
			free(info);
			return (-1);
		}
	}
	if (empty_words(info->head) == true)
		remove_empty_words(&(info->head));
	*node = info->head;
	free(info);
	return (0);
}
