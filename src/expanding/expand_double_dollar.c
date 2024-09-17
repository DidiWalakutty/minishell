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

bool	is_double_dollar(t_token *node, bool heredoc)
{
	int	i;

	i = 0;
	if (node->type != WORD && node->type != DOUBLE_QUOTE || \
		heredoc == true)
		return (false);
	while (i < ft_strlen(node->str))
	{
		if (node->str[i] == '$' && (node->str[i + 1] == '$' || \
			(node->str[i + 2] && node->str[i + 1] == '{' && \
			node->str[i + 2] == '$')))
			return (true);
		i++;
	}
	return (false);
}

t_dollar	*init_double_dol(t_token *node)
{
	t_dollar	*double_dollar;

	double_dollar = mem_check(malloc(sizeof(t_dollar)));
	double_dollar->expanded = ft_itoa(getpid());
	double_dollar->end_var = 0;
	double_dollar->i = 0;
	double_dollar->str_len = ft_strlen(node->str);
	double_dollar->brackets = false;
	double_dollar->no_closing_bracket = false;
	double_dollar->exp_kind = IS_PID;
	return (double_dollar);
}

int	set_pid(t_token *node, t_expand *info)
{
	t_dollar	*dub_var;

	dub_var = init_double_dol(node);
	while (dub_var->i < dub_var->str_len)
	{
		if (node->str[dub_var->i] == '$' && (node->str[dub_var->i + 1] == \
			'$' || node->str[dub_var->i + 1] == '{'))
		{
			if (node->str[dub_var->i + 1] == '{')
				dub_var->brackets = true;
			dub_var->expanded = ft_strdup(dub_var->expanded);
			dub_var->end_var = dub_var->i + 2;
			if (dub_var->brackets == true)
				dub_var->end_var += 2;
			expand_node(node, dub_var);
			dub_var->str_len = ft_strlen(node->str);
			continue ;
		}
		dub_var->i++;
		while (node->str[dub_var->i] && node->str[dub_var->i] != '$')
			dub_var->i++;
		dub_var->str_len = ft_strlen(node->str);
	}
	return (0);
}
