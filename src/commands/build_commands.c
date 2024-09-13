/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build_commands.c                                  :+:    :+:             */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/22 18:14:06 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/13 23:47:19 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	check_cmd_builtin(t_cmd **cmd)
{
	if (!ft_strncmp("cd", (*cmd)->cmd, 3))
		(*cmd)->builtin = CD;
	else if (!ft_strncmp("export", (*cmd)->cmd, 7))
		(*cmd)->builtin = EXPORT;
	else if (!ft_strncmp("unset", (*cmd)->cmd, 6))
		(*cmd)->builtin = UNSET;
	else if (!ft_strncmp("exit", (*cmd)->cmd, 5))
		(*cmd)->builtin = EXIT;
	else if (!ft_strncmp("echo", (*cmd)->cmd, 5))
		(*cmd)->builtin = ECHO_BUILTIN;
	else if (!ft_strncmp("pwd", (*cmd)->cmd, 4))
		(*cmd)->builtin = PWD;
	else if (!ft_strncmp("env", (*cmd)->cmd, 4))
		(*cmd)->builtin = ENV;
}

static void	set_command_and_args(t_token **token, t_cmd **curr_cmd, \
			t_data *data)
{
	if ((*curr_cmd)->cmd == NULL)
	{
		if ((*token)->type == WORD || (*token)->type == SINGLE_QUOTE || \
			(*token)->type == DOUBLE_QUOTE)
		{
			(*curr_cmd)->cmd = ft_strdup((*token)->str);
			check_cmd_builtin(curr_cmd);
			(*curr_cmd)->args = add_to_double_array((*curr_cmd)->args, \
								(*token)->str);
		}
	}
	else
	{
		if ((*token)->type == PIPE)
		{
			(*curr_cmd)->pipe_out = true;
			(*curr_cmd)->next = init_cmds(data);
			(*curr_cmd) = (*curr_cmd)->next;
			(*curr_cmd)->pipe_in = true;
		}
		else
			(*curr_cmd)->args = add_to_double_array((*curr_cmd)->args, \
								(*token)->str);
	}
}

t_cmd	*merge_commands(t_token *tokens, t_data *data)
{
	t_cmd	*command_list;
	t_cmd	*current_cmd;

	command_list = init_cmds(data);
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
			set_command_and_args(&tokens, &current_cmd, data);
		tokens = tokens->next;
	}
	return (command_list);
}

t_cmd	*build_commands(t_token *tokens, t_data *data)
{
	t_cmd		*commands;

	commands = NULL;
	if (tokens && not_just_spaces(tokens) && empty_words(tokens))
	{
		commands = merge_commands(tokens, data);
		commands->env = data->env;
	}
	return (commands);
}
