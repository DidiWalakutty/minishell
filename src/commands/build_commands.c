/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build_commands.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/22 18:14:06 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/10 12:50:22 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*last_list_command(t_cmd *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	push_to_cmd_list(t_cmd **list, t_cmd *new)
{
	t_cmd	*list_node;

	if (*list == NULL)
	{
		*list = new;
	}
	list_node = last_list_command(*list);
	list_node->next = new;
}

void	set_command_and_args(t_token **token, t_cmd **curr_cmd)
{
	if ((*curr_cmd)->command == NULL)
	{
		if ((*token)->type == WORD || (*token)->type == SINGLE_QUOTE || \
			(*token)->type == DOUBLE_QUOTE)
		{
			(*curr_cmd)->command = ft_strdup((*token)->str);
			(*curr_cmd)->args = add_to_double_array((*curr_cmd)->args, \
								(*token)->str);
		}
	}
	else
	{
		if ((*token)->type == PIPE)
		{
			(*curr_cmd)->next = init_cmds();
			(*curr_cmd) = (*curr_cmd)->next;
		}
		else
			(*curr_cmd)->args = add_to_double_array((*curr_cmd)->args, \
								(*token)->str);
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
	while (tokens)
	{
		if (a_redirection(tokens->type) == true)
		{
			if (handle_redirect(&tokens, &current_cmd) != 1)
				printf("check for failure and free");
		}
		else
			set_command_and_args(&tokens, &current_cmd);
		tokens = tokens->next;
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
		commands->env = data->env;
	}
	return (commands);
}
