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
	return (true);
}

static t_dollar	*init_dollar(t_node *node)
{
	t_dollar	*dollar;

	dollar = malloc(sizeof(t_dollar));
	dollar->expanded = NULL;
	dollar->env_name = NULL;
	dollar->str_len = ft_strlen(node->str);
	dollar->i = 0;
	dollar->start_env = 0;
	dollar->end_var = 0;
	dollar->env_length = 0;
	dollar->brackets = false;
	dollar->remainder = false;
	return (dollar);
}

// start_env is $ +1, where ENV-name starts.
// end is where env_name ends.
// Searches the env-name and its info.
static void	expand_dollar(t_node *node, t_dollar *dol, char **env)
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
		dol->end_var++;
	dol->env_name = ft_substr(node->str, dol->start_env, \
					dol->end_var - dol->start_env);
	dol->expanded = copy_env_input(env, dol->env_name);
	if (!dol->expanded)
		dol->expanded = ft_strdup("");
	dol->env_length = ft_strlen(dol->expanded);
	if (dol->brackets == true)
	{
		dol->start_env--;
		dol->end_var++;
	}
	expand_node(node, dol);
	// dol->expanded = NULL;	reset for next check?
}

void	reset_var_info(t_node *node, t_node *head, t_expand *info)
{
	int	temp;

	temp = 0;
	node = head;
	temp = info->node_i;
	while (info->node_i--)
		node = (node)->next;
	info->node_i = temp;
}

// Check for $ as last char?
// Check for if strlen(dol_var->expanded) == 0? If so, free(dol_var) + ret 0;
// This function expands a $-env for the whole D-Q node.
// first while loop: node->next && node->previous == NULL
int	set_dollar(t_node *node, char **env, t_expand *info)
{
	t_dollar	*dol_var;

	dol_var = init_dollar(node);
	while (dol_var->i < dol_var->str_len)
	{
		if (node->str[dol_var->i] == '$' && \
			(if_valid_char(node->str[dol_var->i + 1]) || \
			node->str[dol_var->i + 1] == '{'))
		{
			expand_dollar(node, dol_var, env);
			if (dol_var->remainder == true)
				info->to_next_node = false;
			// break ;
		}
		else
		{
			dol_var->i++;
			while (node->str[dol_var->i] && node->str[dol_var->i] != '$')
				dol_var->i++;
		}
	}
	if (dol_var->i >= dol_var->str_len)
		reset_var_info(node, info->head, info);
	free(dol_var);
	return (0);
}
