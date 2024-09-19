/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_brackets.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: didi <didi@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/14 16:18:18 by didi          #+#    #+#                 */
/*   Updated: 2024/09/18 18:59:57 by didi          ########   odam.nl         */
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

void	reset_joined(t_dollar *var, char **updated_joined, t_joined *join, char *remain)
{
	if ((!remain || remain[0] == '\0') && !join->before || join->before[0] == '\0')
		*updated_joined = ft_strdup("");
	else if (!remain || remain[0] == '\0')
		*updated_joined = ft_strdup(join->before);
	else if (!join->before || join->before[0] == '\0')
		*updated_joined = ft_strdup(remain);
	else
		*updated_joined = ft_strconcat(join->before, remain);
}

bool	check_exit_brackets(char *str, t_dollar *var, char **new_str, \
							t_joined *join)
{
	char	*temp;

	if (var->exp_kind == IS_EXIT || var->exp_kind == IS_PID)
	{
		if (exit_brackets(str, var, var->str_len) == false)
		{
			temp = ft_substr(str, var->end_var - 1, var->str_len);
			reset_joined(var, new_str, join, temp);
			free(temp);
			return (false);
		}
	}
	if (var->exp_kind == IS_DOLLAR)
	{
		if (var->no_closing_bracket == true)
		{
			reset_joined(var, new_str, join, join->remainder);
			return (false);
		}
	}
	return (true);
}
