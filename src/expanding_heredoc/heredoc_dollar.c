/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_dollar.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: didi <didi@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 16:29:08 by didi          #+#    #+#                 */
/*   Updated: 2024/10/01 22:19:37 by diwalaku      ########   odam.nl         */
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

	new = malloc(sizeof(t_h_dol));
	if (!new)
		return (NULL);
	new->copy = ft_strdup(str);
	if (!new->copy)
		return (NULL);
	new->expanded = NULL;
	new->env_name = NULL;
	new->i = 0;
	new->str_len = ft_strlen(str);
	new->start_env = 0;
	new->end_var = 0;
	new->brackets = false;
	new->env_expansion = false;
	new->no_closing_brackets = false;
	new->exp_kind = IS_DOLLAR;
	return (new);
}

void	extract_here_env_variable(char *str, t_h_dol *info)
{
	info->start_env = info->i + 1;
	if (str[info->start_env] == '{')
	{
		info->brackets = true;
		info->start_env++;
	}
	info->end_var = info->start_env;
	while (str[info->end_var] && (is_alph_or_num(str[info->end_var]) || \
			str[info->end_var] == '_'))
	{
		info->end_var++;
		if (str[info->end_var] == '$')
			break ;
	}
	if (info->brackets == true && str[info->end_var] != '}')
		info->no_closing_brackets = true;
	if (info->expanded)
	{
		free(info->expanded);
		info->expanded = NULL;
	}
}

void	set_env_and_expand(char *str, t_h_dol *info, char **env, bool *mal_fail)
{
	extract_here_env_variable(str, info);
	if (info->env_name)
	{
		free(info->env_name);
		info->env_name = NULL;
	}
	info->env_name = ft_substr(str, info->start_env, \
					info->end_var - info->start_env);
	if (!info->env_name)
	{
		*mal_fail = true;
		return ;
	}
	info->expanded = copy_env_input(env, info->env_name);
	if (!info->expanded)
		info->expanded = ft_strdup("");
	if (!info->expanded)
	{
		*mal_fail = true;
		return ;
	}
	if (info->brackets == true && info->no_closing_brackets == false && \
		(info->end_var < info->str_len))
		info->end_var++;
	expand_heredoc_string(str, info, mal_fail);
}

void	process_here_dollar(t_h_dol *info, char **env, bool *mal_fail)
{
	while (info->i < info->str_len)
	{
		if (info->copy[info->i] == '$' && (is_valid(info->copy[info->i \
			+ 1]) || info->copy[info->i + 1] == '{'))
		{
			if (info->copy[info->i + 2] && info->copy[info->i + 2] != '$' && \
				info->copy[info->i + 2] != '?')
			{
				set_env_and_expand(info->copy, info, env, mal_fail);
				if (*mal_fail)
					return ;
				if (info->env_expansion == true)
				{
					info->i++;
					info->env_expansion = false;
				}
				info->str_len = ft_strlen(info->copy);
				continue ;
			}
		}
		info->i++;
		while (info->copy[info->i] && info->copy[info->i] != '$')
			info->i++;
		info->str_len = ft_strlen(info->copy);
	}
}
