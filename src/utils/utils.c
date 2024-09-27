/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                           :+:    :+:             */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 17:06:02 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/21 01:23:16 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		error_exit("Error", EXIT_FAILURE, NULL);
	return (NULL);
}

void	free_all(t_data *data)
{
	free(data->input);
	free_array(data->env);
	free_list(data->list);
	free_cmds(data->cmd_process);
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
			free(info->expanded);
		if (info->env_name)
			free(info->env_name);
		free(info);
	}
}
