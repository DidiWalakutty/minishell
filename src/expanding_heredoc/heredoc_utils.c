/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: didi <didi@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/16 14:03:40 by didi          #+#    #+#                 */
/*   Updated: 2024/09/20 18:51:57 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_joined	*init_here_join(char *str, t_h_dol *info)
{
	t_joined	*new;

	new = mem_check(malloc(sizeof(t_joined)));
	new->before = ft_substr(str, 0, info->i);
	new->remainder = ft_substr(str, info->end_var, info->str_len);
	new->joined = NULL;
	return (new);
}

static void	heredoc_joined_update(t_h_dol *info, t_joined *join, \
			char **updated_join, bool *expanded)
{
	if ((!join->remainder || join->remainder[0] == '\0') && \
		(!join->before || join->before[0] == '\0'))
		*updated_join = ft_strdup("");
	else if (!join->remainder || join->remainder[0] == '\0')
		*updated_join = ft_strdup(join->before);
	else if (!join->before || join->before[0] == '\0')
		*updated_join = ft_strdup(join->remainder);
	else
		*updated_join = ft_strconcat(join->before, join->remainder);
}

void	expand_here_pid(char *str, t_h_dol *info, bool *expanded)
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
	info->expanded = ft_strdup(info->expanded);
	if (!info->expanded)
		info->expanded = ft_strdup("");
	if (info->brackets == true && info->no_closing_brackets == false && \
		info->end_var < info->str_len)
		info->end_var++;
}

void	expand_here_exit(char *str, t_h_dol *info, bool *expanded)
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
	info->expanded = ft_strdup(info->expanded);
	if (!info->expanded)
		info->expanded = ft_strdup("");
	if (info->brackets == true && info->no_closing_brackets == false && \
		info->end_var < info->str_len)
		info->end_var++;
}

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
	if (info->no_closing_brackets == true)
		heredoc_joined_update(info, var, &var->joined, expanded);
	info->copy = ft_strdup(var->joined);
	free(var->before);
	free(var->remainder);
	free(var->joined);
	info->brackets = false;
	info->no_closing_brackets = false;
}
