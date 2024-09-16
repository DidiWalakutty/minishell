/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_exit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: didi <didi@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/16 20:16:15 by didi          #+#    #+#                 */
/*   Updated: 2024/09/16 20:55:43 by didi          ########   odam.nl         */
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

t_h_dol	*init_here_exit(char *str)
{
	t_h_dol	*new;

	new = mem_check(malloc(sizeof(t_h_dol)));
	new->expanded = NULL;
	new->env_name = ft_strdup("0");
	// exit status nodig, bovenstaande voor testing purposes.
	// new->env_name = ft_itoa(data->exit_status); 
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