/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_exit_and_empty.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/02 19:46:22 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/08/21 13:18:06 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_null(t_node **node)
{
	if (*node && ((*node)->null == true))
	{
		*node = (*node)->next;
		return (true);
	}
	return (false);
}

bool	is_exit_status(t_node *node)
{
	int	i;

	i = 0;
	if (node->type != WORD && node->type != DOUBLE_QUOTE)
		return (false);
	while (node->str[i])
	{
		if (node->str[i] == '$' && node->str[i + 1] == '?')
			return (true);
		i++;
	}
	return (false);
}

t_dollar	*init_exit_variables(t_node *node)
{
	t_dollar	*exit_var;

	exit_var = malloc(sizeof(t_dollar));
	exit_var->expanded = NULL;
	exit_var->end_var = 0;
	exit_var->str_len = ft_strlen(node->str);
	exit_var->i = 0;
	return (exit_var);
}

int	set_exit_status(t_data *data, t_node *node, t_expand *info)
{
	t_dollar	*exit_var;
	char		*exit_status;

	exit_status = ft_itoa(data->exit_status);
	exit_var = init_exit_variables(node);
	while (exit_var->i < exit_var->str_len)
	{
		if (node->str[exit_var->i] == '$' && node->str[exit_var->i + 1] == '?')
		{
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
