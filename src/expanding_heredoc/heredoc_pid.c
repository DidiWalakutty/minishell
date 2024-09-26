/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_pid.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: didi <didi@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 17:00:49 by didi          #+#    #+#                 */
/*   Updated: 2024/09/26 20:29:32 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_heredoc_double(char *str, int i)
{
	if (str[i] == '$')
	{
		if (str[i + 1] == '{')
		{
			i += 2;
			if (str[i] == '$')
				return (true);
			return (false);
		}
		if (str[i + 1] == '$')
			return (true);
	}
	return (false);
}

t_h_dol	*init_here_pid(char *str)
{
	t_h_dol	*new;

	new = malloc(sizeof(t_h_dol));
	if (!new)
		return (NULL);
	new->expanded = ft_itoa(getpid());
	if (!new->expanded)
		return (NULL);
	new->copy = ft_strdup(str);
	if (!new->copy)
	{
		free(new->expanded);
		return (NULL);
	}
	new->env_name = NULL;
	new->i = 0;
	new->str_len = ft_strlen(str);
	new->start_env = 0;
	new->end_var = 0;
	new->brackets = false;
	new->no_closing_brackets = false;
	new->exp_kind = IS_PID;
	return (new);
}

void	process_here_pid(char **copy, t_h_dol *info, bool *mal_fail)
{
	while (info->i < info->str_len)
	{
		if (info->copy[info->i] == '$' && (info->copy[info->i + 1] == '$' || \
			(info->copy[info->i + 1] == '{' && info->copy[info->i + 2] == '$')))
		{
			expand_here_pid(info->copy, info, mal_fail);
			if (*mal_fail)
				return ;
			expand_heredoc_string(info->copy, info, mal_fail);
			if (*mal_fail)
				return ;
			info->str_len = ft_strlen(info->copy);
			continue ;
		}
		info->i++;
		while (info->copy[info->i] && info->copy[info->i] != '$')
			info->i++;
		info->str_len = ft_strlen(info->copy);
	}
}
