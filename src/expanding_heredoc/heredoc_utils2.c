/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_utils2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 19:30:27 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/10/01 22:22:02 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_here_before(t_joined *var, bool *mal_fail)
{
	if (var->before && var->before[0] != '\0')
	{
		if (var->joined)
			free(var->joined);
		var->joined = ft_strdup(var->before);
		if (!var->joined)
			*mal_fail = true;
	}
}

static bool	handle_here_expanded(t_joined *var, t_h_dol *info, bool *mal_fail)
{
	char	*temp;

	if (info->expanded && info->expanded[0] != '\0')
	{
		temp = check_joined(var->joined, info->expanded);
		if (!temp)
		{
			*mal_fail = true;
			free(var->joined);
			return (false);
		}
		free(var->joined);
		var->joined = temp;
		if (info->exp_kind == IS_DOLLAR)
			info->env_expansion = true;
	}
	return (true);
}

static bool	handle_here_remainder(t_joined *var, bool *mal_fail)
{
	char	*temp;

	if (var->remainder && var->remainder[0] != '\0')
	{
		temp = check_joined(var->joined, var->remainder);
		if (!temp)
		{
			*mal_fail = true;
			free(var->joined);
			return (false);
		}
		free(var->joined);
		var->joined = temp;
	}
	return (true);
}

void	handle_here_joined_string(t_joined *var, t_h_dol *info, bool *mal_fail)
{
	handle_here_before(var, mal_fail);
	if (*mal_fail)
		return ;
	if (!handle_here_expanded(var, info, mal_fail) || *mal_fail)
		return ;
	if (!handle_here_remainder(var, mal_fail) || *mal_fail)
		return ;
	if (!var->joined)
	{
		var->joined = ft_strdup("");
		if (!var->joined)
		{
			*mal_fail = true;
			return ;
		}
	}
}

void	reset_expansions(t_h_dol *info)
{
	if (info->env_name)
	{
		free(info->env_name);
		info->env_name = NULL;
	}
	if (info->expanded)
	{
		free(info->expanded);
		info->expanded = NULL;
	}
}
