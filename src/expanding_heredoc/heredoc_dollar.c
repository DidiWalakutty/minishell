/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_dollar.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: didi <didi@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 16:29:08 by didi          #+#    #+#                 */
/*   Updated: 2024/09/12 19:20:01 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_heredoc_dollar(char *str, int i)
{
	if (str[i] == '$')
	{
		if (str[i + 1] == '{' && (is_alph_or_num(str[i + 2] || \
			str[i + 1] == '_')))
			return (true);
		else if (is_alph_or_num(str[i + 1] || str[i + 1] == '_'))
			return (true);
	}
	return (false);
}

t_h_dol	*init_heredol(void)
{
	t_h_dol	*new;

	new = mem_check(malloc(sizeof(t_h_dol)));
	new->expanded = NULL;
	new->env_name = NULL;
	new->i = 0;
	new->start_env = 0;
	new->end_var = 0;
	new->brackets = false;
	new->quotes = false;
	new->quote_type = '\0';
	return (new);
}

void	check_quote_and_brackets(char *str, int *i, t_h_dol *var)
{
	if (str[*i - 1] == '\'')
	{
		var->quote_type = '\'';
		var->quotes = true;
	}
	if (str[*i - 1] == '\"')
	{
		var->quote_type = '\"';
		var->quotes = true;
	}
	if (str[*i + 1] == '{')
		var->brackets = true;
}

static bool	update_here_brackets(char *str, t_h_dol *info)
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

void	set_env_and_expand(char *str, int *i, t_h_dol *info, char **env)
{
	int	j;

	j = *i + 1;
	if (str[j] == '{')
		j++;
	info->start_env = j;
	info->end_var = j;
	while (str[info->end_var] && (is_alph_or_num(str[info->end_var] || \
			str[info->end_var] == '_')))
	{
		info->end_var++;
		if (str[info->end_var] == '$')
		{
			// *i = info->end_var; // needed or what does it do then?
			break ;
		}
	}
	info->env_name = ft_substr(str, info->start_env, \
					info->end_var - info->start_env);
	info->expanded = copy_env_input(env, info->env_name);
	if (!info->expanded)
		info->expanded = ft_strdup("");
	if (info->brackets == true)
		update_here_brackets(str, info);
	*i = info->end_var;
}
