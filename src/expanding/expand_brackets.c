/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_brackets.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: didi <didi@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/14 16:18:18 by didi          #+#    #+#                 */
/*   Updated: 2024/09/17 19:44:53 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	exit_brackets(char *str, t_dollar *var, int max)
{
	if (var->exp_kind == IS_EXIT && str[var->i + 1] == '{')
	{
		if (str[var->i + 2] == '?' && (var->i + 3 <= max))
		{
			if (str[var->i + 3] != '}')
				return (false);
		}
		else if (!str[var->i + 3])
			return (false);
	}
	else if (var->exp_kind == IS_PID && str[var->i + 1] == '{')
	{
		if (str[var->i + 2] == '$' && (var->i + 3 <= max))
		{
			if (str[var->i + 3] != '}')
				return (false);
		}
		else if (!str[var->i + 3])
			return (false);
	}
	return (true);
}

void	reset_joined(t_dollar *var, char **updated_joined, t_joined *join)
{
	free(var->expanded);
	if (!join->remainder && !join->before)
		*updated_joined = ft_strdup("");
	else if (!join->remainder)
		*updated_joined = ft_strdup(join->before);
	else if (!join->before)
		*updated_joined = ft_strdup(join->remainder);
	else
		*updated_joined = ft_strconcat(join->before, join->remainder);
}

bool	check_exit_brackets(char *str, t_dollar *var, char **new_str, \
							t_joined *join)
{
	if (var->exp_kind == IS_EXIT || var->exp_kind == IS_PID)
	{
		if (exit_brackets(str, var, var->str_len) == false)
		{
			reset_joined(var, new_str, join);
			return (false);
		}
	}
	if (var->exp_kind == IS_DOLLAR)
	{
		if (var->no_closing_bracket == true)
		{
			free(var->env_name);
			reset_joined(var, new_str, join);
			return (false);
		}
	}
	return (true);
}
