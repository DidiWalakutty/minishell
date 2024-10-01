/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 17:06:02 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/10/01 17:53:19 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid(char c)
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
		{
			free(var->before);
			var->before = NULL;
		}
		if (var->joined)
		{
			free(var->joined);
			var->joined = NULL;
		}
		if (var->remainder)
		{
			free(var->remainder);
			var->remainder = NULL;
		}
		free(var);
	}
}

void	free_all(t_data *data)
{
	free(data->input);
	free_array(data->env);
	free_list(data->list);
	free_cmds(data->cmd_process);
	free_pipefd_allocs(data);
	free(data);
	rl_clear_history();
}

void	error_exit(const char *msg, int status, t_data *data)
{
	if (status == 127 && msg)
	{
		write(STDERR_FILENO, msg, ft_strlen(msg));
		write(STDERR_FILENO, ": command not found\n", 20);
	}
	else if (msg)
		perror(msg);
	if (status == 1127)
		status = 127;
	if (data)
		free_all(data);
	exit(status);
}

void	free_heredoc_info(t_h_dol *info)
{
	if (info)
	{
		if (info->expanded)
		{
			free(info->expanded);
			info->expanded = NULL;
		}
		if (info->env_name)
		{
			free(info->env_name);
			info->env_name = NULL;
		}
		if (info->copy)
		{
			free(info->copy);
			info->copy = NULL;
		}
		free(info);
	}
}
