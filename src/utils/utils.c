/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 17:06:02 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/24 13:49:48 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	if_valid_char(char c)
{
	if (is_alph_or_num(c) || c == '_')
		return (1);
	return (0);
}

void	free_joined_struct(t_joined *var)
{
	if (var)
	{
		if (var->before)
			free(var->before);
		if (var->joined)
			free(var->joined);
		if (var->remainder)
			free(var->remainder);
		free(var);
	}
}

void	error_exit(const char *msg, int status)
{
	if (status == 127)
	{
		write(STDERR_FILENO, msg, ft_strlen(msg));
		write(STDERR_FILENO, ": command not found\n", 20);
	}
	else if (msg)
		perror(msg);
	if (status == 1127)
		status = 127;
	exit(status);
}

void	free_heredoc_info(t_h_dol *info)
{
	if (info)
	{
		if (info->expanded)
			free(info->expanded);
		if (info->env_name)
			free(info->env_name);
		free(info);
	}
}
