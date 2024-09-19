/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 15:35:01 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/13 21:01:54 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_heredoc(t_token *node)
{
	int	i;

	i = 0;
	if (node->type != HERE_DOC)
		return (false);
	while (node->str[i])
	{
		if (node->str[i] == '<' && node->str[i + 1] == '<')
			return (true);
		i++;
	}
	return (false);
}

char	*check_joined(char *before, char *fill_in)
{
	char	*replacement;

	replacement = NULL;
	if (before && before[0] != '\0')
		replacement = ft_strconcat(before, fill_in);
	else
		replacement = ft_strdup(fill_in);
	return (replacement);
}

static t_joined	*init_join(t_token *node, t_dollar *dol)
{
	t_joined	*new;

	new = mem_check(malloc(sizeof(t_joined)));
	new->before = ft_substr(node->str, 0, dol->i);
	new->remainder = ft_substr(node->str, dol->end_var, dol->str_len);
	new->joined = NULL;
	return (new);
}

// 	free(dol->expanded); ???
// Can't free(joined), because it's now owned by ceate_node;
// It would deallocate the memory while the node still needs to use it.
//
// Expand nodes checks and concatenates before expansion, 
// the expansion and the possible remainder, 
// creates a node and adds it to the list.
void	expand_node(t_token *node, t_dollar *dol)
{
	t_joined	*var;

	var = init_join(node, dol);
	if (!node->str)
		return ;
	if (var->before && var->before[0] != '\0')
		var->joined = ft_strdup(var->before);
	if (dol->expanded && dol->expanded[0] != '\0')
		var->joined = check_joined(var->joined, dol->expanded);
	if (var->remainder && var->remainder[0] != '\0')
		var->joined = check_joined(var->joined, var->remainder);
	if (!var->joined)
		var->joined = ft_strdup("");
	// need to update here when ${?
	// Input is: ${USER}${$}$$${?${?}
	if (dol->brackets == true || (dol->exp_kind == IS_DOLLAR && \
								dol->no_closing_bracket == true))
		check_exit_brackets(node->str, dol, &var->joined, var);
	free(node->str);
	node->str = ft_strdup(var->joined);
	free(var->before);
	free(var->remainder);
	free(var->joined);
	// free(dol->expanded);
	// free(dol->env_name);
	dol->brackets = false;
	dol->no_closing_bracket = false;
}

char	*copy_env_input(char **env, char *to_find)
{
	int		i;
	int		find_len;
	char	*result;

	i = 0;
	find_len = ft_strlen(to_find);
	while (env[i])
	{
		if (env[i][find_len] == '=' && \
			ft_strncmp(env[i], to_find, find_len) == 0)
		{
			result = ft_strdup(env[i] + find_len + 1);
			return (result);
		}
		i++;
	}
	return (NULL);
}
