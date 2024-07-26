/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 15:35:01 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/07/26 15:02:00 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_joined(char *before, char *fill_in)
{
	char	*replacement;

	replacement = NULL;
	if (before && before[0] != '\0')
		replacement = ft_strconcat(before, fill_in);
	else
		replacement = ft_strdup(fill_in);
	return (replacement);
}

// 	free(dol->expanded); ???
// Expand nodes checks and concatenates before expansion, 
// the expansion and the possible remainder, creates a node and adds it.
t_node	*expand_node(t_node *node, t_dollar *dol, t_expand *info)
{
	t_node	*new;
	char	*before;
	char	*remainder;
	char	*joined;

	new = NULL;
	joined = NULL;
	before = ft_substr(node->str, 0, dol->i);
	remainder = ft_substr(node->str, dol->end_var, dol->str_len);
	if (before && before[0] != '\0')
		joined = ft_strdup(before);
	if (dol->expanded && dol->expanded[0] != '\0')
		joined = check_joined(joined, dol->expanded);
	if (remainder && remainder[0] != '\0')
	{
		joined = check_joined(joined, remainder);
		dol->remainder = true;
	}
	new = create_node(joined, node->type);
	node_to_list(&info->head, new);
	free(joined);
	free(before);
	free(remainder);
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
