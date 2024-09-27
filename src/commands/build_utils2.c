/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build_utils2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/24 17:09:14 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/24 17:37:12 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	handle_cmd(t_token **token, t_cmd **curr_cmd)
{
	char	*dup_cmd;

	dup_cmd = ft_strdup((*token)->str);
	if (!dup_cmd)
		return ;
	(*curr_cmd)->cmd = dup_cmd;
	check_cmd_builtin(curr_cmd);
}

static int	add_arg(t_cmd **curr_cmd, char *str)
{
	char	**new_args;

	new_args = add_to_double_array((*curr_cmd)->args, str);
	if (!new_args)
	{
		free((*curr_cmd)->cmd);
		(*curr_cmd)->cmd = NULL;
		return (0);
	}
	(*curr_cmd)->args = new_args;
	return (1);
}

void	set_command_and_args(t_token **token, t_cmd **curr_cmd, \
			t_data *data)
{
	if ((*curr_cmd)->cmd == NULL)
	{
		if ((*token)->type == WORD || (*token)->type == SINGLE_QUOTE || \
			(*token)->type == DOUBLE_QUOTE)
		{
			handle_cmd(token, curr_cmd);
			if ((*curr_cmd)->cmd == NULL)
				return ;
			if (add_arg(curr_cmd, (*token)->str) == 0)
				return ;
		}
	}
	else if ((*token)->type == PIPE)
	{
		(*curr_cmd)->pipe_out = true;
		(*curr_cmd)->next = init_cmds(data);
		(*curr_cmd) = (*curr_cmd)->next;
		(*curr_cmd)->pipe_in = true;
	}
	else
	{
		if (add_arg(curr_cmd, (*token)->str) == 0)
			return ;
	}
}
