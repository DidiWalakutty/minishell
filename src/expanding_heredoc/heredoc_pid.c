/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_pid.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: didi <didi@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 17:00:49 by didi          #+#    #+#                 */
/*   Updated: 2024/09/11 19:20:50 by didi          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_heredoc_pid(char *str, int i)
{
	if (str[i] == '$' && str[i + 1] != '\0')
	{
		if (str[i + 1] == '{' && (str[i + 2] != '\0' && str[i + 3] != '\0'))
		{
			if (str[i + 2] == '$' && str[i + 3] == '}')
				return (true);
			return (false);
		}
		if (str[i + 1] == '$')
			return (true);
	}
	return (false);
}

void	expand_heredoc_pid(char *str, int *i, t_h_dol *info, char **env)
{
	int	j;

	j = *i + 1;
	if (str[j] == '{')
		j++;
	info->start_env = j;
	info->end_var = j;
	if (str[j + 1] && (str[j + 1] == '$'))
	{
		if (info->brackets == true)
	}
}