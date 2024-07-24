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

static t_dollar	*init_dollar(int pos, t_node *node)
{
	t_dollar	*dollar;

	dollar = malloc(sizeof(t_dollar));
	dollar->expanded = NULL;
	dollar->env_name = NULL;
	dollar->i = 0;
	dollar->str_len = ft_strlen(node->str);
	dollar->dollar_pos = pos;
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
	// printf("exp part: %s\n", expanded_part->str);
	// node_to_list(expanded_part);
	// printf("Node after expanding is: %s\n", node->str);
	// replace_string(node, var);
	// Replace string is just to check if expanding worked. 
	// We need expand_node to truly replace it. ^^
	// replace_node(replacer) // need to add position in list?
}

int	set_dollar(t_node *node, char **env, t_expand *info)
{
	t_dollar	*dol_var;

	//
	//
	// HERE!
	// Won't continu when there's a remainder
	// "Hi $USER hoi" will continuously loop and not pick up the "hoi".
	// Is the problem in expand_input or set_dollar?
	//
	//
	dol_var = init_dollar(info->i, node);
	while (dol_var->i < dol_var->str_len)
	{
		printf("Loop iteration: dol_var->i = %d, char = %c, str_len = %d\n", dol_var->i, node->str[dol_var->i], dol_var->str_len);
		if (node->str[dol_var->i] == '$' && !node->str[dol_var->i + 1])
		{
			free(dol_var);
			return (0);
		}
		if (node->str[dol_var->i] == '$' && (if_valid_char(node->str[dol_var->i + 1]) || \
			node->str[dol_var->i + 1] == '{'))
		{
			dol_var->dollar_pos = dol_var->i;
			expand_dollar(node, dol_var, env);
			// dol_var->i = dol_var->end_var;
			printf("i in set_dollar is: %i\n", dol_var->i);
			if (dol_var->remainder == true)
			{
				info->to_next_node = false;
				printf("Expansion found remainder, don't go to next node\n");
			}
			break ;
		}
		else
		{
			dol_var->i++;
			while (node->str[dol_var->i] && node->str[dol_var->i] != '$')
			{
				dol_var->i++;
				printf("Else statement: char is: %c|\n", node->str[dol_var->i]);
			}
		}
	}
	if (ft_strlen(dol_var->expanded) == 0)
	{
		printf("strlen dol_var->expanded is 0\n");
		free(dol_var);
		return (0);
	}
	printf("Exiting set_dollar\n");
	free(dol_var);
	return (0);
}
