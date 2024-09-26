/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_utils2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 19:30:27 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/26 19:29:55 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_here_before(t_joined *var, t_h_dol *info, bool *mal_fail)
{
	if (var->before && var->before[0] != '\0')
	{
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
	}
	return (true);
}

static bool	handle_here_remainder(t_joined *var, t_h_dol *info, bool *mal_fail)
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
	handle_here_before(var, info, mal_fail);
	if (*mal_fail)
		return ;
	if (!handle_here_expanded(var, info, mal_fail) || *mal_fail)
		return ;
	if (!handle_here_remainder(var, info, mal_fail) || *mal_fail)
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
