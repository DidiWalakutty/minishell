/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_expanding.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/10 18:10:20 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/26 20:34:38 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (!copy)
	{
		*mal_fail = true;
		return ;
	}
	free_heredoc_info(info);
}

static void	set_heredoc_pid(char **copy, char **env, bool *mal_fail)
{
	t_h_dol	*info;

	info = init_here_pid(*copy);
	if (!info)
	{
		*mal_fail = true;
		return ;
	}
	process_here_pid(copy, info, mal_fail);
	*copy = ft_strdup(info->copy);
	if (!copy)
	{
		*mal_fail = true;
		return ;
	}
	free_heredoc_info(info);
}

static void	set_heredoc_exit(char **copy, t_data *data, bool *mal_fail)
{
	t_h_dol	*info;

	info = init_here_exit(*copy, data->exit_status);
	if (!info)
	{
		*mal_fail = true;
		return ;
	}
	process_here_exit(copy, info, mal_fail);
	*copy = ft_strdup(info->copy);
	if (!copy)
	{
		*mal_fail = true;
		return ;
	}
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
	while (copy[i])
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
