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

	double_dollar = malloc(sizeof(t_dollar));
	if (!double_dollar)
		return (NULL);
	double_dollar->expanded = ft_itoa(getpid());
	if (!double_dollar->expanded)
		return (NULL);
	double_dollar->end_var = 0;
	double_dollar->i = 0;
	double_dollar->str_len = ft_strlen(node->str);
	double_dollar->brackets = false;
	double_dollar->no_closing_bracket = false;
	double_dollar->exp_kind = IS_PID;
	return (double_dollar);
}

static void	expand_pid(t_token *node, t_dollar *dol, t_expand *info)
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
	if (!dol->expanded)
		dol->expanded = ft_strdup("");
	if (!dol->expanded)
	{
		info->mal_fail = true;
		return ;
	}
	if (dol->brackets == true && dol->no_closing_bracket == false && \
		(dol->end_var < dol->str_len))
		dol->end_var++;
}

int	expand_pid_and_node(t_token *node, t_dollar *dol, t_expand *info)
{
	while (dol->i < dol->str_len)
	{
		if (node->str[dol->i] == '$' && (node->str[dol->i + 1] == '$' || \
			(node->str[dol->i + 1] == '{' && node->str[dol-> i + 2] == '$')))
		{
			expand_pid(node, dol, info);
			if (info->mal_fail)
				return (-1);
			expand_node(node, dol, info);
			if (info->mal_fail)
				return (-1);
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

int	set_pid(t_token *node, t_expand *info)
{
	t_dollar	*dol;

	dol = init_double_dol(node);
	if (!dol)
	{
		info->mal_fail = true;
		return (-1);
	}
	expand_pid_and_node(node, dol, info);
	free(dol->expanded);
	free(dol);
	if (info->mal_fail)
		return (-1);
	return (0);
}
