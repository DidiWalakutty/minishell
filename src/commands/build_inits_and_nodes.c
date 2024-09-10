/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build_inits_and_nodes.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/23 15:45:42 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/10 16:37:49 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_redirects(t_cmd *cmd)
{
	cmd->redir_in = NULL;
	cmd->redir_out = NULL;
}

t_cmd	*init_cmds(void)
{
	t_cmd	*command;

	command = mem_check(malloc(sizeof(t_cmd)));
	command->command = NULL;
	command->args = NULL;
	command->redir_in = NULL;
	command->redir_out = NULL;
	command->next = NULL;
	return (command);
}

