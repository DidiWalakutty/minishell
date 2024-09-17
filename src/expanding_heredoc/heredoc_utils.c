/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: didi <didi@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/16 14:03:40 by didi          #+#    #+#                 */
/*   Updated: 2024/09/17 19:29:09 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reset_here_joined(t_h_dol *info, char **update_join, t_joined *join)
{
	if ((!join->remainder || join->remainder[0] == '\0') && (!join->before || \
		join->before[0] == '\0'))
		*update_join = ft_strdup("");
	else if (!join->remainder || join->remainder[0] == '\0')
		*update_join = ft_strdup(join->before);
	else if (!join->before || join->before[0] == '\0')
		*update_join = ft_strdup(join->remainder);
	else
		*update_join = ft_strconcat(join->before, join->remainder);
}

static bool	exit_here_brackets(char *str, t_h_dol *info, int max)
{
	if (info->exp_kind == IS_EXIT && str[info->i + 1] == '{')
	{
		if (str[info->i + 2] == '?' && (info->i + 3 <= max))
		{
			if (str[info->i + 3] == '}')
				return (true);
			else
				return (false);
		}
		else if (!str[info->i + 3])
			return (false);
	}
	else if (info->exp_kind == IS_PID && str[info->i + 1] == '{')
	{
		if (str[info->i + 2] == '$' && (info->i + 3 <= max))
		{
			if (str[info->i + 3] == '}')
				return (true);
			else
				return (false);
		}
		else if (!str[info->i + 3])
			return (false);
	}
	return (false);
}

bool	hexit_brack(char *str, t_h_dol *info, t_joined *join, bool *expand)
{
	if (info->exp_kind == IS_EXIT || info->exp_kind == IS_PID)
	{
		if (exit_here_brackets(str, info, info->str_len) == false)
		{
			reset_here_joined(info, &join->joined, join);
			*expand = false;
			return (false);
		}
	}
	if (info->exp_kind == IS_DOLLAR)
	{
		if (info->no_closing_brackets == true)
		{
			reset_here_joined(info, &join->joined, join);
			*expand = false;
			return (false);
		}
	}
	return (true);
}

static t_joined	*init_here_join(char *str, t_h_dol *info)
{
	t_joined	*new;

	new = mem_check(malloc(sizeof(t_joined)));
	new->before = ft_substr(str, 0, info->i);
	new->remainder = ft_substr(str, info->end_var, info->str_len);
	new->joined = NULL;
	return (new);
}

// Also needs to receive exit-status
void	expand_heredoc_string(char *str, t_h_dol *info, bool *expanded)
{
	t_joined	*var;

	var = init_here_join(str, info);
	if (!str || !var)
		return ;
	if (var->before && var->before[0] != '\0')
		var->joined = ft_strdup(var->before);
	if (info->expanded && info->expanded[0] != '\0')
		var->joined = check_joined(var->joined, info->expanded);
	if (var->remainder && var->remainder[0] != '\0')
		var->joined = check_joined(var->joined, var->remainder);
	if (!var->joined)
		var->joined = ft_strdup("");
	if (info->brackets == true || (info->exp_kind == IS_DOLLAR && \
									info->no_closing_brackets == true))
		hexit_brack(str, info, var, expanded);
	info->copy = ft_strdup(var->joined);
	free(var->before);
	free(var->remainder);
	free(var->joined);
	info->brackets = false;
	info->no_closing_brackets = false;
}
