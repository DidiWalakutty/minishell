/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   child_redirect.c                                  :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/09/27 19:44:25 by sreerink      #+#    #+#                 */
/*   Updated: 2024/09/27 19:44:26 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	redirect_input(t_cmd *cmd, int fd_in[])
{
	close(fd_in[1]);
	if (!cmd->redir_in && !cmd->pipe_in)
		close(fd_in[0]);
	else if (!cmd->redir_in && cmd->pipe_in)
	{
		if (!redirect_fd(fd_in[0], STDIN_FILENO))
			return (false);
	}
	else
	{
		close(fd_in[0]);
		if (redirect_redir_in(cmd->redir_in) == 1)
			return (false);
	}
	return (true);
}

bool	redirect_output(t_cmd *cmd, int fd_out[])
{
	close(fd_out[0]);
	if (!cmd->redir_out && !cmd->pipe_out)
		close(fd_out[1]);
	else if (!cmd->redir_out && cmd->pipe_out)
	{
		if (!redirect_fd(fd_out[1], STDOUT_FILENO))
			return (false);
	}
	else
	{
		close(fd_out[0]);
		if (redirect_redir_out(cmd->redir_out) == 1)
			return (false);
	}
	return (true);
}
