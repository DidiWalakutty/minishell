/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_dollar.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/23 22:00:24 by anonymous     #+#    #+#                 */
/*   Updated: 2024/06/23 22:00:24 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_dollar_position(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

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
	dollar->start = 0;
	dollar->end = 0;
	dollar->dollar_pos = pos;
	dollar->brackets = false;
	return (dollar);
}

static void	expand_dollar(t_node *node, t_dollar *var, char **env)
{
	var->start = var->dollar_pos + 1;
	if (node->str[var->end] == '{')
	{
		var->brackets = true;
		var->start++;
	}
	var->end = var->start;
	while (node->str[var->end] && (is_alph_or_num(node->str[var->end]) || \
			node->str[var->end] == '_'))
		var->end++;
	var->env_name = ft_substr(node->str, var->start, var->end - var->start);
	var->expanded = copy_env_input(env, var->env_name);
	if (var->brackets == true)
	{
			var->start--;
			var->end++;
	}
	replace_string(node, var);
	// replace_node(replacer) // need to add position in list?
}

void	set_dollar(t_node *node, char **env, t_expand *info)
{
	t_dollar	*dol_var;
	int			i;

	dol_var = init_dollar(info->i);
	i = 0;
	while (node->str[i])
	{	
		// if (node->str[i] == '$' && !node->str[i + 1])
		// 	return (free(dol_var));
		if (node->str[i] == '$' && (if_valid_char(node->str[i + 1]) || \
			node->str[i + 1] == '{'))
		{
			// HERE: Make sure the string is concactenated.
			dol_var->dollar_pos = i;
			// printf("Original string is: %s\n", node->str);
			expand_dollar(node, dol_var, env);
			// printf("Expanded env string is: %s\n", dol_var->expanded);
			// printf("New string is: %s\n", node->str);
			break ;
		}
		else
		{
			i++;
			// while != '$', i++;
		}
	}
}