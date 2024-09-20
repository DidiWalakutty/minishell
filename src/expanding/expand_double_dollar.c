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

static void	expand_pid(t_token *node, t_dollar *dol)
{
	dol->start_env = dol->i + 1;
	if (node->str[dol->start_env] == '{')
	{
		dol->brackets = true;
		dol->start_env++;
	}
	dol->end_var = dol->start_env;
	if (node->str[dol->end_var] == '$')
		dol->end_var++;
	if (dol->brackets == true && node->str[dol->end_var] != '}')
		dol->no_closing_bracket = true;
	dol->expanded = ft_strdup(dol->expanded);
	if (!dol->expanded)
		dol->expanded = ft_strdup("");
	if (dol->brackets == true && dol->no_closing_bracket == false && \
		(dol->end_var < dol->str_len))
		dol->end_var++;
}

int	set_pid(t_token *node, t_expand *info)
{
	t_dollar	*dol;

	dol = init_double_dol(node);
	while (dol->i < dol->str_len)
	{
		if (node->str[dol->i] == '$' && (node->str[dol->i + 1] == '$' || \
			(node->str[dol->i + 1] == '{' && node->str[dol-> i + 2] == '$')))
		{
			expand_pid(node, dol);
			expand_node(node, dol);
			dol->str_len = ft_strlen(node->str);
			continue ;
		}
		dol->i++;
		while (node->str[dol->i] && node->str[dol->i] != '$')
			dol->i++;
		dol->str_len = ft_strlen(node->str);
	}
	return (0);
}
