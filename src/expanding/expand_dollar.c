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

static t_dollar	*init_dollar(int pos)
{
	t_dollar	*dollar;

	dollar = malloc(sizeof(t_dollar));
	dollar->expanded = NULL;
	dollar->env_name = NULL;
	dollar->i = 0;
	dollar->str_len = 0;
	dollar->dollar_pos = pos;
	dollar->start_env = 0;
	dollar->end_var = 0;
	dollar->env_length = 0;
	dollar->brackets = false;
	return (dollar);
}

// start_env is $ +1, where EVN-name starts.
// end is where env_name ends.
static void	expand_dollar(t_node *node, t_dollar *var, char **env)
{
	t_node	*expanded_part;

	expanded_part = NULL;
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
	expanded_part = expand_node(node, var);
	// printf("exp part: %s\n", expanded_part->str);
	// replace_string(node, var);
	// Replace string is just to check if expanding worked. 
	// We need expand_node to truly replace it. ^^
	// replace_node(replacer) // need to add position in list?
}

int	set_dollar(t_node *node, char **env, t_expand *info)
{
	t_dollar	*dol_var;

	dol_var = init_dollar(info->i);
	dol_var->str_len = ft_strlen(node->str);
	while (dol_var->i < dol_var->str_len)
	{
		if (node->str[dol_var->i] == '$' && !node->str[dol_var->i + 1])
		{
			free(dol_var);
			return (0);
		}
		else if (node->str[dol_var->i] == '$' && (if_valid_char(node->str[dol_var->i + 1]) || \
			node->str[dol_var->i + 1] == '{'))
		{
			dol_var->dollar_pos = dol_var->i;
			expand_dollar(node, dol_var, env);
			continue;
		}
		else
		{
			dol_var->i++;
			// while (node->str[dol_var->i] && node->str[dol_var->i] != '$')
			// {
			// 	dol_var->i++;
			// 	// printf("Else statement: char is: %c|\n", node->str[dol_var->i]);
			// }
			// printf("char end else-loop: %c|\n", node->str[dol_var->i]);
		}
	}
	return (0);
}
