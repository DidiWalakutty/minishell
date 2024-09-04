/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build_commands.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/22 18:14:06 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/08/23 18:03:57 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_command_and_args(t_token **token, t_cmd **curr_cmd)
{
	if ((*curr_cmd)->command == NULL)
	{
		if ((*token)->type == WORD || (*token)->type == SINGLE_QUOTE || \
			(*token)->type == DOUBLE_QUOTE)
		{
			(*curr_cmd)->command = (*token)->str;
			(*curr_cmd)->args = add_to_double_array((*curr_cmd)->args, (*token)->str);
		}
	}
	else
	{
		if (a_redirection((*token)->type) || (*token)->type == PIPE)
			return ;
		else
			(*curr_cmd)->args = add_to_double_array((*curr_cmd)->args, (*token)->str);
	}
}

// Need to push to list when another pipe is found or if we have no more tokens!
t_cmd	*merge_commands(t_token *tokens, t_data *data)
{
	t_cmd	*command_list;
	t_cmd	*current_cmd;

	command_list = init_cmds();
	current_cmd = command_list;
	init_redirects(current_cmd);
	int i = 0;
	while (tokens)
	{
		if (a_redirection(tokens->type) == true)
		{
			if (handle_redirect(&tokens, &current_cmd) != 1)
				printf("check for failure and free");
		}
		// else if (tokens->type == PIPE)
		// 	push_to_cmd_list();
		else
			set_command_and_args(&tokens, &current_cmd);
		tokens = tokens->next;
	}
	while (current_cmd->redir_in) 
	{
        printf("Input Redirection: %s\n", current_cmd->redir_in->str);
        current_cmd->redir_in = current_cmd->redir_in->next;
    }
	
	while (current_cmd->redir_out) 
	{
        printf("Output Redirection: %s\n", current_cmd->redir_out->str);
        current_cmd->redir_out = current_cmd->redir_out->next;
    }
	while (current_cmd->args[i])
	{
		printf("%s\n", current_cmd->args[i]);
		i++;
	}
	return (command_list);
}

t_cmd	*build_commands(t_token *tokens, t_data *data)
{
	t_cmd		*commands;

	commands = NULL;
	if (tokens && not_just_spaces(tokens))
	{
		commands = merge_commands(tokens, data);
		// if (!commands)
			// printf("free things\n");
		// handle_them
	}
	return (commands);
}
