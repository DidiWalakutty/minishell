/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_expanding.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/10 18:10:20 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/24 20:07:21 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	set_heredoc_dollar(char **copy, char **env, bool *mal_fail)
// {
// 	t_h_dol	*info;

// 	info = init_here_dol(*copy);
// 	while (info->i < info->str_len)
// 	{
// 		if (info->copy[info->i] == '$' && (if_valid_char(info->copy[info->i \
// 			+ 1]) || info->copy[info->i + 1] == '{'))
// 		{
// 			if (info->copy[info->i + 2] && info->copy[info->i + 2] != '$' && \
// 				info->copy[info->i + 2] != '?')
// 			{
// 				set_env_and_expand(info->copy, info, env);
// 				info->str_len = ft_strlen(info->copy);
// 				continue ;
// 			}
// 		}
// 		info->i++;
// 		while (info->copy[info->i] && info->copy[info->i] != '$')
// 			info->i++;
// 		info->str_len = ft_strlen(info->copy);
// 	}
// 	*copy = ft_strdup(info->copy);
// 	free_heredoc_info(info);
// }

static void	set_heredoc_dollar(char **copy, char **env, bool *mal_fail)
{
	t_h_dol	*info;

	info = init_here_dol(*copy);
	if (!info)
	{
		*mal_fail = true;
		return ;
	}
	process_here_dollar(copy, info, env, mal_fail);
	*copy = ft_strdup(info->copy);
	free_heredoc_info(info);
}

static int	set_heredoc_pid(char **copy, char **env, bool *mal_fail)
{
	t_h_dol	*info;

	info = init_here_pid(*copy);
	if (!info)
	{
		*mal_fail = true;
		return (-1);
	}
	while (info->i < info->str_len)
	{
		if (info->copy[info->i] == '$' && (info->copy[info->i + 1] == '$' || \
			(info->copy[info->i + 1] == '{' && info->copy[info->i + 2] == '$')))
		{
			expand_here_pid(info->copy, info);
			expand_heredoc_string(info->copy, info);
			info->str_len = ft_strlen(info->copy);
			continue ;
		}
		info->i++;
		while (info->copy[info->i] && info->copy[info->i] != '$')
			info->i++;
		info->str_len = ft_strlen(info->copy);
	}
	*copy = ft_strdup(info->copy);
	free_heredoc_info(info);
}

static void	set_heredoc_exit(char **copy, t_data *data, bool *mal_fail)
{
	t_h_dol	*info;

	info = init_here_exit(*copy, data->exit_status);
	while (info->i < info->str_len)
	{
		if (info->copy[info->i] == '$' && (info->copy[info->i + 1] == '?' || \
			(info->copy[info->i + 1] == '{' && info->copy[info->i + 2] == '?')))
		{
			expand_here_exit(info->copy, info);
			expand_heredoc_string(info->copy, info);
			info->str_len = ft_strlen(info->copy);
			continue ;
		}
		info->i++;
		while (info->copy[info->i] && info->copy[info->i] != '$')
			info->i++;
		info->str_len = ft_strlen(info->copy);
	}
	*copy = ft_strdup(info->copy);
	free_heredoc_info(info);
}

char	*heredoc_expanding(char *str, t_data *data)
{
	char	*new_str;
	char	*copy;
	bool	mal_fail;
	int		i;

	i = 0;
	mal_fail = false;
	copy = ft_strdup(str);
	if (!copy)
		return (NULL);
	while (str[i])
	{
		if (is_heredoc_dollar(copy, i))
			set_heredoc_dollar(&copy, data->env, &mal_fail);
		if (is_heredoc_double(copy, i))
			set_heredoc_pid(&copy, data->env, &mal_fail);
		if (is_heredoc_exit(copy, i))
			set_heredoc_exit(&copy, data, &mal_fail);
		if (mal_fail == true)
			return (free(copy), NULL);
		i++;
	}
	new_str = ft_strdup(copy);
	free(copy);
	return (new_str);
}
