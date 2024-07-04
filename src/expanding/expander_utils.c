/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diwalaku <diwalaku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:35:01 by diwalaku          #+#    #+#             */
/*   Updated: 2024/07/04 21:42:00 by diwalaku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Or t_node *new???
// static char	*attach_expand(char *before, char *replace)
// {
// 	char	*new;

// 	new = ft_strconcat(before, replace);
// 	return (new);
// }

// Replaces the expansion-part in the node.
t_node	*expand_node(t_node *node, t_dollar *var)
{
	t_node	*new;
	t_node	*current;
	char	*before;
	char	*replace;
	char	*remaining;
	char	*joined;
	// char	*joined2;

	new = NULL;
	current = NULL;
	joined = NULL;
	before = ft_substr(node->str, 0, var->dollar_pos);
	replace = ft_substr(var->expanded, 0, var->env_length);
	remaining = ft_substr(node->str, var->end_var, var->str_len);
	if (ft_strlen(before) > 0)
	{
		node_to_list(&new, create_node(before));
		current = new;
		while (current->next != NULL)
			current = current->next;
	}
	printf("current->str after before is: |%s|\n", current->str);
	printf("new->str after before is: |%s|\n", new->str);
	if (ft_strlen(replace) > 0)
	{
		if (current)
		{
			joined = ft_strconcat(current->str, replace);
			free(current->str);
			current->str = joined;
		}
		else
		{
			// node_to_list(&new, create_node(var->expanded));
			joined = ft_strdup(replace);
			current = create_node(joined);
			node_to_list(&new, current);
		}
	}
	printf("current->str after replace is: |%s|\n", current->str);
	printf("new->str after replace is: |%s|\n", new->str);
	// if (ft_strlen(remaining) > 0)
	// {
	// 	node_to_list(&new, create_node(remaining));
	// 	current = new;
	// 	while (current->next != NULL)
	// 		current = current->next;
	// }
	// printf("after remain check: |%s|\n", new->str);
	// free(before);
	// free(replace);
	// free(remaining);
	return (new);
}

		// joined = attach_expand(before, var->expanded);
		// printf("Joined is: %s\n", joined);
		// node_to_list(&new, create_node(joined));
		// // HERE: Doesn't update the node to joined!!!
		// printf("After +expand is: %s\n", new->str);
		// joined = ft_strconcat(current->str, var->expanded);
		// free(current->str);
		// current->str = joined;
		// node_to_list(&new, create_node(joined));
	// }
	// if (ft_strlen(remaining) > 0)
	// {
	// 	joined2 = ft_strconcat(current->str, remaining);
	// 	free(current->str);
	// 	current->str = joined2;
	// 	node_to_list(&new, create_node(joined2));
	// }
	// free(before);
	// free(remaining);
// 	return (new);
// }

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
