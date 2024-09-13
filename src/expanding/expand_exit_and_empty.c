/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_exit_and_empty.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/02 19:46:22 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/12 19:53:23 by diwalaku      ########   odam.nl         */
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
	if (node->str[i] && node->str[i + 1])
	{
		if (node->str[i] == '$' && (node->str[i + 1] == '?' || \
			node->str[i + 1] == '{'))
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
	return (exit_var);
}

int	set_exit_status(t_data *data, t_token *node, t_expand *info)
{
	t_dollar	*exit_var;
	char		*exit_status;

	exit_status = ft_itoa(data->exit_status);
	exit_var = init_exit_variables(node);
	while (exit_var->i < exit_var->str_len)
	{
		if (node->str[exit_var->i] == '$' && (node->str[exit_var->i + 1] == \
			'?' || node->str[exit_var->i + 1] == '{'))
		{
			if (node->str[exit_var->i + 1] == '{')
				exit_var->brackets = true;
			exit_var->expanded = exit_status;
			exit_var->end_var = exit_var->i + 2;
			expand_node(node, exit_var);
		}
		exit_var->i++;
		while (node->str[exit_var->i] && node->str[exit_var->i] != '$')
			exit_var->i++;
		exit_var->str_len = ft_strlen(node->str);
	}
	return (0);
}
