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

void	set_command(t_token **token, t_cmd **commands, t_cmd_v **var)
{
	// if token
	if ((*var)->command == NULL)
	{
		if ((*token)->type == WORD || (*token)->type == SINGLE_QUOTE || \
			(*token)->type == DOUBLE_QUOTE)
		{
			(*var)->command = (*token)->str;
			(*var)->arguments = add_to_double_array((*var)->arguments, (*token)->str);	
		}
	}
	else
	{
		if ((*token)->type == PIPE)
		{

			printf("Pipe found\n");
		}
		else
		{
			(*var)->arguments = add_to_double_array((*var)->arguments, (*token)->str);
		}
	}
	// if !token->next, push the command.
}		

t_cmd	*merge_commands(t_token *tokens, t_data *data)
{
	t_cmd	*commands;
	t_cmd_v	*tracker;

	tracker = init_tracker();
	commands = init_cmds();
	while (tokens)
	{
		if (redir_in)
			handle_in;
		else if (redir_out)
			handle_out;
		// if (a_redirection(tokens->type) == true)
		// {
		// 	if (handle_redirect(&tokens, &commands, data) != 1)
		// 		printf("check for failure and free");
		// }
		set_command(&tokens, &commands, &tracker);
		tokens = tokens->next;
	}
	return (commands);
}

t_cmd	*build_commands(t_token *tokens, t_data *data)
{
	t_cmd		*commands;

	commands = NULL;
	if (tokens && not_just_spaces(tokens))
	{
		commands = merge_commands(tokens, data);
		// if (!commands)
			printf("free things\n");
		// handle_them
	}
	return (commands);
}
