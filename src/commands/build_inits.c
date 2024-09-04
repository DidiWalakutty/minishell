/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build_inits.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/23 15:45:42 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/08/23 17:55:54 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_redirects(t_cmd *cmd)
{
	cmd->redir_in = NULL;
	cmd->redir_out = NULL;
	// cmd->redir_in = malloc(sizeof(t_redir_in));
	// if (!cmd->redir_in)
	// 	error_exit("Failed to allocate memory for redir_in", EXIT_FAILURE);
	// cmd->redir_in->str = NULL;
	// cmd->redir_in->heredoc = false;
	// cmd->redir_in->quotes = false;
	// cmd->redir_in->next = NULL;

	// cmd->redir_out = malloc(sizeof(t_redir_out));
	// if (!cmd->redir_out)
	// 	error_exit("Failed to allocate memory for redir_out", EXIT_FAILURE);
	// cmd->redir_out->str = NULL;
	// cmd->redir_out->append = false;
	// cmd->redir_out->next = NULL;
}

t_cmd	*init_cmds(void)
{
	t_cmd	*command;

	command = malloc(sizeof(t_cmd));
	command->command = NULL;
	command->args = NULL;
	command->type = EMPTY;
	command->redir_in = NULL;
	command->redir_out = NULL;
	command->next = NULL;
	return (command);
}
