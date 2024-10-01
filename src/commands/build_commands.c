/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build_commands.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/22 18:14:06 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/10/01 17:25:39 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// command_list holds the head of the list.
// current_cmd is used to traverse and modify the list.
t_cmd	*merge_commands(t_token *tokens, t_data *data)
{
	t_cmd	*command_list;
	t_cmd	*current_cmd;

	command_list = init_cmds(data);
	if (!command_list)
		return (NULL);
	current_cmd = command_list;
	init_redirects(current_cmd);
	while (tokens)
	{
		if (a_redirection(tokens->type) == true)
		{
			if (handle_redirect(&tokens, &current_cmd) == 1)
				return (free_cmds(command_list), NULL);
		}
		else
		{
			set_command_and_args(&tokens, &current_cmd, data);
			if (current_cmd->cmd == NULL && tokens->type != PIPE)
				return (free_cmds(command_list), NULL);
		}
		tokens = tokens->next;
	}
	return (command_list);
}

t_cmd	*build_commands(t_token **tokens, t_data *data)
{
	t_cmd		*commands;

	commands = NULL;
	if (*tokens && not_just_spaces(*tokens))
	{
		commands = merge_commands(*tokens, data);
		if (commands)
			commands->env = data->env;
		else
			error_exit("malloc", EXIT_FAILURE, data);
	}
	return (commands);
}
