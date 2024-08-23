/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build_redirections.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/23 13:07:59 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/08/23 18:01:50 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	a_redirection(t_type type)
{
	if (type == REDIR_IN || type == REDIR_OUT || \
		type == APPEND || type == HERE_DOC)
		return (true);
	return (false);
}

static t_redir_type	set_type(t_type type, t_cmd *command)
{
	t_redir_type	redir_type;

	redir_type = UNCLEAR;
	command->redir->heredoc = false;
	command->redir->append = false;
	if (type == REDIR_IN || type == HERE_DOC)
	{
		redir_type = RED_IN;
		if (type == HERE_DOC)
			command->redir->heredoc = true;
	}
	else if (type == REDIR_OUT || type == APPEND)
	{
		redir_type = RED_OUT;
		if (type == APPEND)
			command->redir->append = true;
	}
	return (redir_type);
}

static char	*get_filename(t_token **token, t_type type, bool *quotes)
{
	char	*result;

	result = NULL;
	if (type == WORD || type == SINGLE_QUOTE || type == DOUBLE_QUOTE)
	{
		result = ft_strdup((*token)->str);
		if (type == SINGLE_QUOTE || type == DOUBLE_QUOTE)
			*quotes = true;
	}
	return (result);
}

int	handle_redirect(t_token **token, t_cmd **command, t_data *data)
{
	t_cmd		*cmd;
	t_redir_in	*temp_in;
	t_redir_out	*temp_out;

	cmd = *command;
	temp_in = cmd->redir_in;
	temp_out = cmd->redir_out;
	init_temp_in();
	init_temp_out();
	while (*token)
	{
		if (a_redirection((*token)->type))
		{
			// handle_in
			// handle_out
			cmd->redir->type = set_type((*token)->type, cmd);
			(*token) = (*token)->next;
			{
				cmd->redir->filename = get_filename(token, (*token)->type, \
				&(cmd->redir->quotes));
			}
		}
		(*token) = (*token)->next;
	}
	if (!token || !cmd->redir->filename)
		return (0);
	return (1);
}
