/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_utils2.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 12:50:46 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/26 21:45:57 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_null(t_token **node)
{
	if (*node && ((*node)->null == true))
	{
		*node = (*node)->next;
		return (true);
	}
	return (false);
}

static void	handle_before(t_joined *var, t_expand *info)
{
	if (var->before && var->before[0] != '\0')
	{
		var->joined = ft_strdup(var->before);
		if (!var->joined)
			info->mal_fail = true;
	}
}

static bool	handle_expanded(t_joined *var, t_dollar *dol, t_expand *info)
{
	char	*temp;

	if (dol->expanded && dol->expanded[0] != '\0')
	{
		temp = check_joined(var->joined, dol->expanded);
		if (!temp)
		{
			info->mal_fail = true;
			free(var->joined);
			return (false);
		}
		free(var->joined);
		var->joined = temp;
		if (dol->exp_kind == IS_DOLLAR)
			dol->env_expansion = true;
	}
	return (true);
}

static bool	handle_remainder(t_joined *var, t_expand *info)
{
	char	*temp;

	if (var->remainder && var->remainder[0] != '\0')
	{
		temp = check_joined(var->joined, var->remainder);
		if (!temp)
		{
			info->mal_fail = true;
			free(var->joined);
			return (false);
		}
		free(var->joined);
		var->joined = temp;
	}
	return (true);
}

void	handle_joined_strings(t_joined *var, t_dollar *dol, t_expand *info)
{
	handle_before(var, info);
	if (info->mal_fail)
		return ;
	if (!handle_expanded(var, dol, info) || info->mal_fail)
		return ;
	if (!handle_remainder(var, info) || info->mal_fail)
		return ;
	if (!var->joined)
	{
		var->joined = ft_strdup("");
		if (!var->joined)
		{
			info->mal_fail = true;
			return ;
		}
	}
}
