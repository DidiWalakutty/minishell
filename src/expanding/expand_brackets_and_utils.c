/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_brackets_and_utils.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: didi <didi@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/14 16:18:18 by didi          #+#    #+#                 */
/*   Updated: 2024/09/24 18:14:07 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_joined(t_joined *join, char **updated_joined, t_expand *info)
{
	if ((!join->remainder || join->remainder[0] == '\0') && \
		(!join->before || join->before[0] == '\0'))
	{
		*updated_joined = ft_strdup("");
		if (!*updated_joined)
			info->mal_fail = true;
	}
	else if (!join->remainder || join->remainder[0] == '\0')
	{
		*updated_joined = ft_strdup(join->before);
		if (!*updated_joined)
			info->mal_fail = true;
	}
	else if (!join->before || join->before[0] == '\0')
	{
		*updated_joined = ft_strdup(join->remainder);
		if (!*updated_joined)
			info->mal_fail = true;
	}
	else
	{
		*updated_joined = ft_strconcat(join->before, join->remainder);
		if (!*updated_joined)
			info->mal_fail = true;
	}
}

void	extract_env_variable(t_token *node, t_dollar *dol)
{
	dol->start_env = dol->i + 1;
	if (node->str[dol->start_env] == '{')
	{
		dol->brackets = true;
		dol->start_env++;
	}
	dol->end_var = dol->start_env;
	while (node->str[dol->end_var] && (is_alph_or_num(node->str[dol->end_var]) \
		|| node->str[dol->end_var] == '_'))
	{
		dol->end_var++;
		if (node->str[dol->end_var] == '$')
			break ;
	}
	if (dol->brackets == true && node->str[dol->end_var] != '}')
		dol->no_closing_bracket = true;
}
