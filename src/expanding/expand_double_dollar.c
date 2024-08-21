/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_double_dollar.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 15:27:10 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/07/04 15:27:10 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_double_dollar(t_node *node)
{
	int	i;

	i = 0;
	if (node->type != WORD && node->type != DOUBLE_QUOTE)
		return (false);
	while (node->str[i])
	{
		if (node->str[i] == '$' && node->str[i + 1] == '$')
			return (true);
		i++;
	}
	return (false);
}

t_dollar	*init_double_dol(t_node *node)
{
	t_dollar	*double_dollar;

	double_dollar = malloc(sizeof(t_dollar));
	double_dollar->expanded = NULL;
	double_dollar->end_var = 0;
	double_dollar->str_len = ft_strlen(node->str);
	double_dollar->i = 0;
	return (double_dollar);
}

int	set_pid(t_node *node, t_expand *info)
{
	t_dollar	*dub_var;
	char		*pid;

	pid = ft_itoa(getpid());
	dub_var = init_double_dol(node);
	while (dub_var->i < dub_var->str_len)
	{
		if (node->str[dub_var->i] == '$' && node->str[dub_var->i + 1] == '$')
		{
			dub_var->expanded = pid;
			dub_var->end_var = dub_var->i + 2;
			expand_node(node, dub_var);
		}
		dub_var->i++;
		while (node->str[dub_var->i] && node->str[dub_var->i] != '$')
			dub_var->i++;
		dub_var->str_len = ft_strlen(node->str);
	}
	return (0);
}
