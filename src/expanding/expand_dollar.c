/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_dollar.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 15:24:51 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/07/04 15:24:51 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_dollar(t_token *node, bool heredoc)
{
	char	*copy;

	if (node->type != WORD && node->type != DOUBLE_QUOTE || \
		heredoc == true)
		return (false);
	copy = ft_strchr(node->str, '$');
	if (!copy)
		return (false);
	return (true);
}

static t_dollar	*init_dollar(t_token *node)
{
	t_dollar	*dollar;

	dollar = malloc(sizeof(t_dollar));
	if (!dollar)
		return (NULL);
	dollar->expanded = NULL;
	dollar->env_name = NULL;
	dollar->str_len = ft_strlen(node->str);
	dollar->i = 0;
	dollar->start_env = 0;
	dollar->end_var = 0;
	dollar->brackets = false;
	dollar->no_closing_bracket = false;
	dollar->exp_kind = IS_DOLLAR;
	return (dollar);
}

static void	expand_dollar(t_token *node, t_dollar *dol, char **env, \
							t_expand *info)
{
	extract_env_variable(node, dol);
	dol->env_name = ft_substr(node->str, dol->start_env, \
					dol->end_var - dol->start_env);
	if (!dol->env_name)
	{
		info->mal_fail = true;
		return ;
	}
	dol->expanded = copy_env_input(env, dol->env_name);
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
	expand_node(node, dol, info);
}

static void	process_dollar(t_token *node, t_dollar *dol_var, char **env, \
							t_expand *info)
{
	while (dol_var->i < dol_var->str_len)
	{
		if (node->str[dol_var->i] == '$' && \
			(if_valid_char(node->str[dol_var->i + 1]) || \
			(node->str[dol_var->i + 1] == '{')))
		{
			if (node->str[dol_var->i + 2] && (node->str[dol_var->i + 2] \
							!= '?' && node->str[dol_var->i + 2] != '$'))
			{
				expand_dollar(node, dol_var, env, info);
				if (info->mal_fail == true)
					return ;
				dol_var->str_len = ft_strlen(node->str);
				continue ;
			}
		}
		dol_var->i++;
		while (node->str[dol_var->i] && node->str[dol_var->i] != '$')
			dol_var->i++;
		dol_var->str_len = ft_strlen(node->str);
	}
}

int	set_dollar(t_token *node, char **env, t_expand *info)
{
	t_dollar	*dol_var;

	dol_var = init_dollar(node);
	if (!dol_var)
	{
		info->mal_fail = true;
		return (-1);
	}
	process_dollar(node, dol_var, env, info);
	free(dol_var);
	return (0);
}
