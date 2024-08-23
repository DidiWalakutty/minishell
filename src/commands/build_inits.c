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

t_cmd_v	*init_tracker(void)
{
	t_cmd_v	*tracker;

	tracker = malloc(sizeof(t_cmd_v));
	tracker->command = NULL;
	tracker->arguments = NULL;
	return (tracker);
}

t_redir_in	*init_temp_in(void)
{
	t_redir_in	*in;

	in = malloc(sizeof(t_redir_in));
	in->str = NULL;
	in->heredoc = false;
	in->quotes = false;
	in->next = NULL;
	return (in);
}

t_redir_out	*init_temp_out(void)
{
	t_redir_out	*out;

	out = malloc(sizeof(t_redir_out));
	out->str = NULL;
	out->append = false;
	out->next = NULL;
	return (out);
}

// static t_redir	*init_redir(void)
// {
// 	t_redir	*redir;

// 	redir = malloc(sizeof(t_redir));
// 	redir->type = UNCLEAR;
// 	redir->filename = NULL;
// 	redir->append = false;
// 	redir->heredoc = false;
// 	redir->quotes = false;
// 	redir->next = NULL;
// 	return (redir);
// }

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
