/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build_redirections.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/23 13:07:59 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/24 17:08:32 by diwalaku      ########   odam.nl         */
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

static int	get_filename(t_token *token, t_cmd *cmd, t_redir_type type)
{
	char	*result;
	int		create_status;

	result = NULL;
	create_status = 0;
	if (token->type == WORD || token->type == SINGLE_QUOTE || \
		token->type == DOUBLE_QUOTE)
	{
		result = ft_strdup(token->str);
		if (!result)
			return (1);
		if (type == RED_IN || type == HEREDOC)
			create_status = create_redir_in(cmd, result, type, token->type);
		else if (type == RED_OUT || type == APPENDING)
			create_status = create_redir_out(cmd, result, type);
		if (create_status == 1)
		{
			free(result);
			return (1);
		}
		free(result);
		return (0);
	}
	return (1);
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
			if (get_filename(*token, cmd, type) == 1)
			{
				printf("Error: Memory allocation failed\n");
				return (1);
			}
		}
		else
		{
			printf("Error: expected a filename after redirection\n");
			return (1);
		}
	}
	return (0);
}
