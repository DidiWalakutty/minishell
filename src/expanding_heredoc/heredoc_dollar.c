/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_dollar.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: didi <didi@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 16:29:08 by didi          #+#    #+#                 */
/*   Updated: 2024/09/16 21:38:18 by didi          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_heredoc_dollar(char *str, int i)
{
	if (str[i] == '$')
	{
		if (str[i + 1] == '{')
		{
			i += 2;
			if (str[i] == '?' || str[i] == '$')
				return (false);
			if (is_alph_or_num(str[i]) || str[i] == '_')
				return (true);
		}
		else if (is_alph_or_num(str[i + 1]) || str[i + 1] == '_')
			return (true);
	}
	return (false);
}

t_h_dol	*init_here_dol(char *str)
{
	t_h_dol	*new;

	new = mem_check(malloc(sizeof(t_h_dol)));
	new->expanded = NULL;
	new->env_name = NULL;
	new->copy = ft_strdup(str);
	new->i = 0;
	new->str_len = ft_strlen(str);
	new->start_env = 0;
	new->end_var = 0;
	new->brackets = false;
	new->no_closing_brackets = false;
	new->exp_kind = IS_DOLLAR;
	return (new);
}

// void	check_quote_and_brackets(char *str, int *i, t_h_dol *var)
// {
// 	// Probably don't need to check for the quotes, because it'll
// 	// add them to the new_string anyways.
// 	if (str[*i - 1] == '\'')
// 	{
// 		var->quote_type = '\'';
// 		var->quotes = true;
// 	}
// 	if (str[*i - 1] == '\"')
// 	{
// 		var->quote_type = '\"';
// 		var->quotes = true;
// 	}
// 	if (str[*i + 1] == '{')
// 	{
// 		var->brackets = true;
// 		(*i)++;
// 	}
// }

bool	update_here_brackets(char *str, t_h_dol *info)
{
	if (str[info->end_var + ft_strlen(info->expanded) + 1] != '}')
	{
		info->expanded = ft_strdup("");
		return (false);
	}
	info->start_env--;
	info->end_var--;
	return (true);
}

void	set_env_and_expand(char *str, t_h_dol *info, char **env, bool *expanded)
{
	info->start_env = info->i + 1;
	if (str[info->start_env] == '{')
	{
		info->brackets = true;
		info->start_env++;
	}
	info->end_var = info->start_env;
	while (str[info->end_var] && (is_alph_or_num(str[info->end_var]) || str[info->end_var] == '_'))
	{
		info->end_var++;
		if (str[info->end_var] == '$')
			break;
	}
	if (info->brackets == true && str[info->end_var] != '}')
		info->no_closing_brackets = true;
	info->env_name = ft_substr(str, info->start_env, \
					info->end_var - info->start_env);
	info->expanded = copy_env_input(env, info->env_name);
	if (!info->expanded)
		info->expanded = ft_strdup("");
	if (info->brackets == true && info->no_closing_brackets == false && (info->end_var < info->str_len))
		info->end_var++;
	expand_heredoc_string(str, info, expanded);
}
