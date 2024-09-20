/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/14 18:36:22 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/20 22:45:10 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_expand	*init_info(t_token *list)
{
	t_expand	*info;

	info = mem_check(malloc(sizeof(t_expand)));
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
static int	node_expansion(t_token *node, t_expand *info, t_data *data)
{
	bool		heredoc;
	bool		mal_fail;

	heredoc = false;
	mal_fail = false;

	while (node)
	{
		if (check_null(&node) == true)
			continue ;
		if (node->type == HERE_DOC)
			skip_heredoc_and_spaces(&node, &heredoc);
		if (is_dollar(node, heredoc) == true && mal_fail == false)
			set_dollar(node, data->env, info);
		if (is_double_dollar(node, heredoc) == true)
			set_pid(node, info);
		if (is_exit_status(node, heredoc) == true)
			set_exit_status(data, node, info);
		heredoc = false;
		if (mal_fail == true)
			return (-1);
		node = node->next;
	}
}

void	expand_input(t_data *data, t_token *node, char **env)
{
	t_expand	*info;

	info = init_info(node);
	if (!info)
		return (NULL);
	if (node_expansion(node, info, data) == -1)
	{
		free(info);
		return (NULL);
	}
	if (quote_type_present(info->head) == true)
	{
		if (concatenate_quotes(info->head) == -1)
		{
			free(info);
			return (NULL);
		}
	}
	node = info->head;
	free(info);
}

// Currently problems with brackets and end-var