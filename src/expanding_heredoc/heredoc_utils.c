/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: didi <didi@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/16 14:03:40 by didi          #+#    #+#                 */
/*   Updated: 2024/10/01 17:57:15 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_joined	*init_here_join(char *str, t_h_dol *info)
{
	t_joined	*new;

	new = malloc(sizeof(t_joined));
	if (!new)
		return (NULL);
	new->before = ft_substr(str, 0, info->i);
	if (!new->before)
	{
		free(new);
		return (NULL);
	}
	new->remainder = ft_substr(str, info->end_var, info->str_len);
	if (!new->remainder)
	{
		free(new->before);
		free(new);
		return (NULL);
	}
	new->joined = NULL;
	return (new);
}

static void	reset_here_joined(t_joined *join, \
			char **updated_joined, bool *mal_fail)
{
	if ((!join->remainder || join->remainder[0] == '\0') && \
		(!join->before || join->before[0] == '\0'))
	{
		*updated_joined = ft_strdup("");
		if (!*updated_joined)
			*mal_fail = true;
	}
	else if (!join->remainder || join->remainder[0] == '\0')
	{
		*updated_joined = ft_strdup(join->before);
		if (!*updated_joined)
			*mal_fail = true;
	}
	else if (!join->before || join->before[0] == '\0')
	{
		*updated_joined = ft_strdup(join->remainder);
		if (!*updated_joined)
			*mal_fail = true;
	}
	else
	{
		*updated_joined = ft_strconcat(join->before, join->remainder);
		if (!*updated_joined)
			*mal_fail = true;
	}
}

void	expand_here_pid(char *str, t_h_dol *info, bool *mal_fail)
{
	info->start_env = info->i + 1;
	if (str[info->start_env] == '{')
	{
		info->brackets = true;
		info->start_env++;
	}
	info->end_var = info->start_env;
	if (str[info->end_var] == '$')
		info->end_var++;
	if (info->brackets == true && str[info->end_var] != '}')
		info->no_closing_brackets = true;
	if (!info->expanded)
	{
		*mal_fail = true;
		return ;
	}
	if (info->brackets == true && info->no_closing_brackets == false && \
		info->end_var < info->str_len)
		info->end_var++;
}

void	expand_here_exit(char *str, t_h_dol *info, bool *mal_fail)
{
	info->start_env = info->i + 1;
	if (str[info->start_env] == '{')
	{
		info->brackets = true;
		info->start_env++;
	}
	info->end_var = info->start_env;
	if (str[info->end_var] == '?')
		info->end_var++;
	if (info->brackets == true && str[info->end_var] != '}')
		info->no_closing_brackets = true;
	if (!info->expanded)
	{
		*mal_fail = true;
		return ;
	}
	if (info->brackets == true && info->no_closing_brackets == false && \
		info->end_var < info->str_len)
		info->end_var++;
}

void	expand_heredoc_string(char *str, t_h_dol *info, bool *mal_fail)
{
	t_joined	*var;

	var = init_here_join(str, info);
	if (!str || !var)
	{
		free_joined_struct(var);
		return ;
	}
	handle_here_joined_string(var, info, mal_fail);
	if (check_mal_fail(mal_fail, var))
		return ;
	if (info->no_closing_brackets == true)
	{
		free(var->joined);
		reset_here_joined(var, &var->joined, mal_fail);
	}
	if (check_mal_fail(mal_fail, var))
		return ;
	free(info->copy);
	info->copy = ft_strdup(var->joined);
	if (!info->copy)
		*mal_fail = true;
	free_joined_struct(var);
	info->brackets = false;
	info->no_closing_brackets = false;
}
