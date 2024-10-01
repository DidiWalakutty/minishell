/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build_inits_and_nodes.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/23 15:45:42 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/13 20:28:07 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_redirects(t_cmd *cmd)
{
	cmd->redir_in = NULL;
	cmd->redir_out = NULL;
}

t_cmd	*init_cmds(t_data *data)
{
	t_cmd	*command;

	command = malloc(sizeof(t_cmd));
	if (!command)
		return (NULL);
	command->cmd = NULL;
	command->pid = 0;
	command->path = NULL;
	command->args = NULL;
	command->env = data->env;
	command->redir_in = NULL;
	command->redir_out = NULL;
	command->pipe_in = false;
	command->pipe_out = false;
	command->builtin = NO_BUILTIN;
	command->next = NULL;
	return (command);
}
