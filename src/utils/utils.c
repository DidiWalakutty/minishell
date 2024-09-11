/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 17:06:02 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/11 19:09:57 by didi          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_valid_char(char c)
{
	if (is_alph_or_num(c) || c == '_')
		return (1);
	return (0);
}

void	*mem_check(void *pointer)
{
	if (pointer != NULL)
		return (pointer);
	else
		error_exit("Error", EXIT_FAILURE);
	return (NULL);
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