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

t_dollar	*init_exit_variables(t_token *node, t_data *data)
{
	t_dollar	*exit_var;

	exit_var = malloc(sizeof(t_dollar));
	if (!exit_var)
		return (NULL);
	exit_var->expanded = ft_itoa(data->exit_status);
	if (!exit_var->expanded)
		return (NULL);
	exit_var->env_name = NULL;
	exit_var->start_env = 0;
	exit_var->end_var = 0;
	exit_var->str_len = ft_strlen(node->str);
	exit_var->i = 0;
	exit_var->brackets = false;
	exit_var->no_closing_bracket = false;
	exit_var->exp_kind = IS_EXIT;
	return (exit_var);
}

static void	expand_exit(t_token *node, t_dollar *ex, t_expand *info)
{
	ex->start_env = ex->i + 1;
	if (node->str[ex->start_env] == '{')
	{
		ex->brackets = true;
		ex->start_env++;
	}
	ex->end_var = ex->start_env;
	if (node->str[ex->end_var] == '?')
		ex->end_var++;
	if (ex->brackets == true && node->str[ex->end_var] != '}')
		ex->no_closing_bracket = true;
	if (!ex->expanded)
		ex->expanded = ft_strdup("");
	if (!ex->expanded)
	{
		info->mal_fail = true;
		return ;
	}
	if (ex->brackets == true && ex->no_closing_bracket == false && \
		(ex->end_var < ex->str_len))
		ex->end_var++;
}

static int	expand_exit_and_node(t_token *node, t_dollar *ex, t_expand *info)
{
	expand_exit(node, ex, info);
	if (info->mal_fail)
		return (-1);
	expand_node(node, ex, info);
	if (info->mal_fail)
		return (-1);
	return (0);
}

int	set_exit_status(t_data *data, t_token *node, t_expand *info)
{
	t_dollar	*ex;

	ex = init_exit_variables(node, data);
	if (!ex)
	{
		info->mal_fail = true;
		return (-1);
	}
	while (ex->i < ex->str_len)
	{
		if (node->str[ex->i] == '$' && (node->str[ex->i + 1] == '?' || \
			(node->str[ex->i + 1] == '{' && node->str[ex->i + 2] == '?')))
		{
			if (expand_exit_and_node(node, ex, info) == -1)
				break ;
			ex->str_len = ft_strlen(node->str);
			continue ;
		}
		ex->i++;
		while (node->str[ex->i] && node->str[ex->i] != '$')
			ex->i++;
		ex->str_len = ft_strlen(node->str);
	}
	free(ex->expanded);
	free(ex);
	if (info->mal_fail)
		return (-1);
	return (0);
}
