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

	dollar = mem_check(malloc(sizeof(t_dollar)));
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

static bool	update_dol_brackets(t_token *node, t_dollar *dol)
{
	if (node->str[dol->end_var + ft_strlen(dol->expanded) + 1] != '}')
	{
		// free(dol->expanded);
		dol->expanded = ft_strdup("");
		return (false);
	}
	dol->start_env--;
	dol->end_var++;
	return (true);
}

// start_env is $ +1, where ENV-name starts.
// end is where env_name ends.
// Searches the env-name and its info.
static void	expand_dollar(t_token *node, t_dollar *dol, char **env)
{
	dol->start_env = dol->i + 1;
	if (node->str[dol->start_env] == '{')
	{
		dol->brackets = true;
		dol->start_env++;
	}
	dol->end_var = dol->start_env;
	while (node->str[dol->end_var] && (is_alph_or_num(node->str[dol->end_var]) \
		|| node->str[dol->end_var] == '_'))
	{
		dol->end_var++;
		if (node->str[dol->end_var] == '$')
			break ;
	}
	if (dol->brackets == true && node->str[dol->end_var] != '}')
		dol->no_closing_bracket = true;
	dol->env_name = ft_substr(node->str, dol->start_env, \
					dol->end_var - dol->start_env);
	dol->expanded = copy_env_input(env, dol->env_name);
	if (!dol->expanded)
		dol->expanded = ft_strdup("");
	if (dol->brackets == true && dol->no_closing_bracket == false && \
		(dol->end_var < dol->str_len))
		dol->end_var++;
	expand_node(node, dol);
}

// This function expands a $-env for the whole D-Q node.
int	set_dollar(t_token *node, char **env, t_expand *info)
{
	t_dollar	*dol_var;

	dol_var = init_dollar(node);
	while (dol_var->i < dol_var->str_len)
	{
		if (node->str[dol_var->i] == '$' && \
			(if_valid_char(node->str[dol_var->i + 1]) || \
			(node->str[dol_var->i + 1] == '{')))
		{
			if (node->str[dol_var->i + 2] && (node->str[dol_var->i + 2] \
							!= '?' && node->str[dol_var->i + 2] != '$'))
			{
				expand_dollar(node, dol_var, env);
				dol_var->str_len = ft_strlen(node->str);
				continue ;
			}
		}
		dol_var->i++;
		while (node->str[dol_var->i] && node->str[dol_var->i] != '$')
			dol_var->i++;
		dol_var->str_len = ft_strlen(node->str);
	}
	free(dol_var);
	return (0);
}
