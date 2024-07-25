/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 15:35:01 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/07/25 14:33:52 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*expand_node(t_node *node, t_dollar *var, t_expand *info)
{
	t_node	*new;
	char	*before;
	char	*remainder;
	char	*joined;

	new = NULL;
	joined = NULL;
	before = ft_substr(node->str, 0, var->i);
	remainder = ft_substr(node->str, var->end_var, var->str_len);
	if (ft_strlen(before) > 0)
		joined = ft_strdup(before);
	if (ft_strlen(var->expanded) > 0)
		joined = ft_strconcat(before, var->expanded);
	if (ft_strlen(remainder) > 0)
	{
		joined = ft_strconcat(joined, remainder);
		var->remainder = true;
	}
	// free(node->str);
	new = create_node(joined);
	new->type = node->type;
	// node->str = joined;
	node_to_list(&info->head, new);
	// node_to_list(&new, create_node(joined));
	// free(before);
	// free(var->expanded);
	// free(remainder);
	return (new);
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
		if (env[i][find_len] == '=' && \
			ft_strncmp(env[i], to_find, find_len) == 0)
			return (env[i] + find_len + 1);
		i++;
	}
	return (NULL);
}
