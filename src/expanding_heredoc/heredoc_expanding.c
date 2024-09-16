/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_expanding.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/10 18:10:20 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/16 22:24:24 by didi          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_heredoc_dollar(char **copy, char **new_string, char **env, bool *expanded)
{
	t_h_dol	*info;

	info = init_here_dol(*copy);
	while (info->i < info->str_len)
	{
		if (info->copy[info->i] == '$' && (if_valid_char(info->copy[info->i + 1]) || \
			info->copy[info->i + 1] == '{'))
		{
			if (info->copy[info->i + 2] && info->copy[info->i + 2] != '$' && \
				info->copy[info->i + 2] != '?')
			{
				set_env_and_expand(info->copy, info, env, expanded);
				info->str_len = ft_strlen(info->copy);
				continue;
			}
		}
		info->i++;
		while (info->copy[info->i] && info->copy[info->i] != '$')
			info->i++;
		info->str_len = ft_strlen(info->copy);
	}
	*copy = ft_strdup(info->copy);
	free_heredoc_info(info);
}

static void	set_heredoc_pid(char **copy, char **new_string, char **env, bool *expanded)
{
	t_h_dol	*info;

	info = init_here_pid(*copy);
	while (info->i < info->str_len)
	{
		if (info->copy[info->i] == '$' && (info->copy[info->i + 1] == '$' || \
			info->copy[info->i + 1] == '{'))
		{
			if (info->copy[info->i + 1] == '{')
				info->brackets = true;
			info->expanded = ft_strdup(info->env_name);
			info->end_var = info->i + 2;
			if (info->brackets == true)
				info->end_var += 2;
			expand_heredoc_string(info->copy, info, expanded);
			info->str_len = ft_strlen(info->copy);
			continue;
		}
		info->i++;
		while (info->copy[info->i] && info->copy[info->i] != '$')
			info->i++;
		info->str_len = ft_strlen(info->copy);
	}
	*copy = ft_strdup(info->copy);
	free_heredoc_info(info);
}

static void	set_heredoc_exit(char **copy, char **new_string, char **env, bool *expanded)
{
	t_h_dol *info;

	info = init_here_exit(*copy);
	while (info->i < info->str_len)
	{
		if (info->copy[info->i] == '$' && (info->copy[info->i + 1] == '?' || \
			info->copy[info->i + 1] == '{'))
		{
			if (info->copy[info->i + 1] == '{')
				info->brackets = true;
			info->expanded = ft_strdup(info->env_name);
			info->end_var = info->i + 2;
			if (info->brackets == true)
				info->end_var += 2;
			expand_heredoc_string(info->copy, info, expanded);
			info->str_len = ft_strlen(info->copy);
			continue;
		}
		info->i++;
		while (info->copy[info->i] && info->copy[info->i] != '$')
			info->i++;
		info->str_len = ft_strlen(info->copy);
	}
	*copy = ft_strdup(info->copy);
	free_heredoc_info(info);
}

char	*heredoc_expanding(char *str, char **env)
{
	char	*new_str;
	char	*copy;
	int		i;
	bool	expanded;

	i = 0;
	copy = ft_strdup(str);
	new_str = ft_strdup("");
	while (str[i])
	{
		expanded = true;
		if (is_heredoc_dollar(copy, i))
			set_heredoc_dollar(&copy, &new_str, env, &expanded);
		if (is_heredoc_double(copy, i))
			set_heredoc_pid(&copy, &new_str, env, &expanded);
		if (is_heredoc_exit(copy, i))
			set_heredoc_exit(&copy, &new_str, env, &expanded);
		if (expanded == true)
			i++;
	}
	free(new_str);
	new_str = ft_strdup(copy);
	free(copy);
	return (new_str);
}


