/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   trials.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 15:24:51 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/07/25 12:29:40 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_dollar(t_node *node, bool is_expandable)
{
	char	*copy;

	if (is_expandable == false || (node->type != WORD && \
		node->type != DOUBLE_QUOTE))
		return (false);
	copy = ft_strchr(node->str, '$');
	if (!copy)
		return (false);
	if (ft_strlen(copy) >= 1 && ((if_valid_char(copy[1])) || copy[1] == '{'))
		return (true);
	return (false);
}

static t_dollar	*init_dollar(t_node *node)
{
	t_dollar	*dollar;

	dollar = malloc(sizeof(t_dollar));
	dollar->expanded = NULL;
	dollar->env_name = NULL;
	dollar->i = 0;
	dollar->str_len = ft_strlen(node->str);
	dollar->dollar_pos = 0;
	dollar->start_env = 0;
	dollar->end_var = 0;
	dollar->env_length = 0;
	dollar->brackets = false;
	dollar->remainder = false;
	return (dollar);
}

// start_env is $ +1, where ENV-name starts.
// end is where env_name ends.
static void	expand_dollar(t_node *node, t_dollar *var, char **env)
{
	var->dollar_pos = var->i;
	var->start_env = var->dollar_pos + 1;
	if (node->str[var->start_env] == '{')
	{
		var->brackets = true;
		var->start_env++;
	}
	var->end_var = var->start_env;
	while (node->str[var->end_var] && (is_alph_or_num(node->str[var->end_var]) \
			|| node->str[var->end_var] == '_'))
		var->end_var++;
	var->env_name = ft_substr(node->str, var->start_env, \
					var->end_var - var->start_env);
	var->expanded = copy_env_input(env, var->env_name);
	var->env_length = ft_strlen(var->expanded);
	if (var->brackets == true)
	{
		var->start_env--;
		var->end_var++;
	}
	var->i = var->end_var;
	expand_node(node, var);
}

int	set_dollar(t_node *node, char **env, t_expand *info)
{
	t_dollar	*d_var;

	d_var = init_dollar(node);
	while (d_var->i < d_var->str_len)
	{
		if (node->str[d_var->i] == '$' && !node->str[d_var->i + 1])
		{
			free(d_var);
			return (0);
		}
		if ((node->str[d_var->i] == '$') && if_valid_char(node->str[d_var->i +1] \
			|| node->str[d_var->i + 1] == '{'))
		{
			expand_dollar(node, d_var, env);
			if (d_var->remainder == true)
			{
				info->to_next_node = false;
				
			}
			break ;
		}
		else
		{
			d_var->i++;
			while (node->str[d_var->i] && node->str[d_var->i] != '$')
				d_var->i++;
		}
	}
	if (ft_strlen(d_var->expanded) == 0)
	{
		free(d_var);
		return (0);
	}
	free(d_var);
	return (0);
}
// 34 lines