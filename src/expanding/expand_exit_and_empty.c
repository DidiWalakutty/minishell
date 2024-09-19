/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_exit_and_empty.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/02 19:46:22 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/13 20:58:53 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_null(t_token **node)
{
	if (*node && ((*node)->null == true))
	{
		*node = (*node)->next;
		return (true);
	}
	return (false);
}

// wont return true if input is: ${?}
bool	is_exit_status(t_token *node, bool heredoc)
{
	int	i;

	i = 0;
	if (node->type != WORD && node->type != DOUBLE_QUOTE || \
		heredoc == true)
		return (false);
	while (i < ft_strlen(node->str))
	{
		if (node->str[i] == '$' && (node->str[i + 1] == '?' || \
			(node->str[i + 2] && node->str[i + 1] == '{' && \
			node->str[i + 2] == '?')))
			return (true);
		i++;
	}
	return (false);
}

t_dollar	*init_exit_variables(t_token *node)
{
	t_dollar	*exit_var;

	exit_var = mem_check(malloc(sizeof(t_dollar)));
	exit_var->expanded = NULL;
	exit_var->env_name = NULL;
	exit_var->end_var = 0;
	exit_var->str_len = ft_strlen(node->str);
	exit_var->i = 0;
	exit_var->brackets = false;
	exit_var->no_closing_bracket = false;
	exit_var->exp_kind = IS_EXIT;
	return (exit_var);
}

int	set_exit_status(t_data *data, t_token *node, t_expand *info)
{
	t_dollar	*ex;
	char		*exit_status;

	exit_status = ft_itoa(data->exit_status);
	ex = init_exit_variables(node);
	while (ex->i < ex->str_len)
	{
		if (node->str[ex->i] == '$' && (node->str[ex->i + 1] == '?' || \
			(node->str[ex->i + 1] == '{' && node->str[ex->i + 2] == '?')))
		{
			if (node->str[ex->i + 1] == '{')
				ex->brackets = true;
			ex->expanded = exit_status;
			ex->end_var = ex->i + 2;
			if (ex->brackets == true)
				ex->end_var += 2;
			expand_node(node, ex);
		}
		ex->i++;
		while (node->str[ex->i] && node->str[ex->i] != '$')
			ex->i++;
		ex->str_len = ft_strlen(node->str);
	}
	return (0);
}
