/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build_redirections.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/23 13:07:59 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/10 15:42:32 by diwalaku      ########   odam.nl         */
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
	if (type == REDIR_IN)
		redir_type = RED_IN;
	else if (type == REDIR_OUT)
		redir_type = RED_OUT;
	else if (type == HERE_DOC)
		redir_type = HEREDOC;
	else if (type == APPEND)
		redir_type = APPENDING;
	return (redir_type);
}

static void	get_filename(t_token *token, t_cmd *cmd, t_redir_type type)
{
	char		*result;

	result = NULL;
	if (token->type == WORD || token->type == SINGLE_QUOTE || \
		token->type == DOUBLE_QUOTE)
	{
		result = ft_strdup(token->str);
		if (type == RED_IN || type == HEREDOC)
			create_redir_in(cmd, result, type, token->type);
		else if (type == RED_OUT || type == APPENDING)
			create_redir_out(cmd, result, type);
		free(result);
	}
}

int	handle_redirect(t_token **token, t_cmd **command)
{
	t_cmd			*cmd;
	t_redir_type	type;

	cmd = *command;
	if (*token)
	{
		if (a_redirection((*token)->type))
		{
			type = set_type((*token)->type, cmd);
			(*token) = (*token)->next;
			get_filename(*token, cmd, type);
		}
		else
		{
			printf("Error: expected a filename after redirection\n");
			return (0);
		}
	}
	return (1);
}
