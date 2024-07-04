/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/14 18:46:43 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/07/04 11:56:38 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_valid_char(char c)
{
	if (is_alph_or_num(c) || c == '_')
		return (1);
	return (0);
}

// Replaces the expansion-part in the node.
t_node	*expand_node(t_node *node, t_dollar *var)
{
	t_node	*temp;
	char	*before;
	char	*replace;
	char	*remaining;

	temp = NULL;
	before = ft_substr(node->str, 0, var->dollar_pos);
	replace = ft_substr(var->expanded, 0, var->env_length);
	remaining = ft_substr(node->str, var->end_var, var->str_len);
	if (ft_strlen(before) > 0)
	{
		attach_list_token(&temp, create_node(before));
		temp->type = node->type;
	}
	if (ft_strlen(replace) > 0)
		//
	// if (ft_strlen(remaining) > 0)
		// attach_list_token(&temp, create_node(remaining));	
	// return (temp);
}

// Creates new string and replaces the node itself.
void	replace_string(t_node *node, t_dollar *var)
{
	char	*before;
	char	*replace;

	before = ft_strndup(node->str, var->dollar_pos);
	replace = ft_strjoin(before, var->expanded);
	node->str = replace;
}

// Compares each line of env with the given string, like
// pwd, user etc.
char	*copy_env_input(char **env, char *to_find)
{
	int	i;
	int	find_len;

	i = 0;
	find_len = ft_strlen(to_find);
	while (env[i])
	{
		if (env[i][find_len] == '=' && ft_strncmp(env[i], to_find, find_len) == 0)
			return (env[i] + find_len + 1);
		i++;
	}	
	return (NULL);
}
