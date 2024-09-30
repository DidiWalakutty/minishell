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

char	*check_joined(char *before, char *fill_in)
{
	char	*replacement;

	replacement = NULL;
	if (before && before[0] != '\0')
	{
		replacement = ft_strconcat(before, fill_in);
		if (!replacement)
			return (NULL);
	}
	else
	{
		replacement = ft_strdup(fill_in);
		if (!replacement)
			return (NULL);
	}
	return (replacement);
}

static t_joined	*init_join(t_token *node, t_dollar *dol)
{
	t_joined	*new;

	new = malloc(sizeof(t_joined));
	if (!new)
		return (NULL);
	new->before = ft_substr(node->str, 0, dol->i);
	if (!new->before)
	{
		free(new);
		return (NULL);
	}
	new->remainder = ft_substr(node->str, dol->end_var, dol->str_len);
	if (!new->remainder)
	{
		free(new->before);
		free(new);
		return (NULL);
	}
	new->joined = NULL;
	return (new);
}

bool	check_mal_fail(bool *mal_fail, t_joined *var)
{
	if (*mal_fail)
	{
		free_joined_struct(var);
		return (true);
	}
	return (false);
}

void	expand_node(t_token *node, t_dollar *dol, t_expand *info)
{
	t_joined	*var;

	var = init_join(node, dol);
	if (!node->str || !var)
	{
		free_joined_struct(var);
		return ;
	}
	handle_joined_strings(var, dol, info);
	if (check_mal_fail(&info->mal_fail, var))
		return ;
	if (dol->no_closing_bracket)
	{
		free(var->joined);
		reset_joined(var, &var->joined, info);
	}
	if (check_mal_fail(&info->mal_fail, var))
		return ;
	free(node->str);
	node->str = ft_strdup(var->joined);
	if (!node->str)
		info->mal_fail = true;
	free_joined_struct(var);
	dol->brackets = false;
	dol->no_closing_bracket = false;
}

char	*copy_env_input(char **env, char *to_find)
{
	int		i;
	int		find_len;
	int		env_len;
	char	*result;

	i = 0;
	find_len = ft_strlen(to_find);
	while (env[i])
	{
		env_len = ft_strlen(env[i]);
		if (env_len >= find_len && env[i][find_len] == '=' \
		&& ft_strncmp(env[i], to_find, find_len))
		{
			result = ft_strdup(env[i] + find_len + 1);
			if (!result)
				return (NULL);
			return (result);
		}
		i++;
	}
	return (NULL);
}
