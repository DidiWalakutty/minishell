/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_exit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: didi <didi@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/16 20:16:15 by didi          #+#    #+#                 */
/*   Updated: 2024/09/24 15:24:52 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_heredoc_exit(char *str, int i)
{
	if (str[i] == '$')
	{
		if (str[i + 1] == '{')
		{
			i += 2;
			if (str[i] == '?')
				return (true);
			return (false);
		}
		if (str[i + 1] == '?')
			return (true);
	}
	return (false);
}

t_h_dol	*init_here_exit(char *str, int exit)
{
	t_h_dol	*new;

	new = malloc(sizeof(t_h_dol));
	// if (!new)
	new->expanded = ft_itoa(exit);
	new->env_name = NULL;
	new->copy = ft_strdup(str);
	new->i = 0;
	new->str_len = ft_strlen(str);
	new->start_env = 0;
	new->end_var = 0;
	new->brackets = false;
	new->no_closing_brackets = false;
	new->exp_kind = IS_EXIT;
	return (new);
}
