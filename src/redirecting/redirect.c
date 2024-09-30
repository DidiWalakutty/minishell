/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   redirect.c                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/09/27 17:22:09 by sreerink      #+#    #+#                 */
/*   Updated: 2024/09/28 00:41:33 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	redirect_fd(int fd, int fd_dst)
{
	if (dup2(fd, fd_dst) == -1)
	{
		close(fd);
		perror("dup2");
		return (false);
	}
	close(fd);
	return (true);
}

int	redirect_redir_in(t_redin *redir_in)
{
	int	file;

	while (redir_in)
	{
		if (!redir_in->heredoc)
		{
			file = open(redir_in->str, O_RDONLY);
			if (file == -1)
			{
				perror(redir_in->str);
				return (EXIT_FAILURE);
			}
			if (!redirect_fd(file, STDIN_FILENO))
				return (EXIT_FAILURE);
		}
		else if (!redir_in->next)
		{
			close(redir_in->pipe_hdoc[1]);
			if (!redirect_fd(redir_in->pipe_hdoc[0], STDIN_FILENO))
				return (EXIT_FAILURE);
		}
		redir_in = redir_in->next;
	}
	return (EXIT_SUCCESS);
}

int	redirect_redir_out(t_redou *redir_out)
{
	int	file;

	while (redir_out)
	{
		if (redir_out->append)
			file = open(redir_out->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			file = open(redir_out->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file == -1)
		{
			perror(redir_out->str);
			return (EXIT_FAILURE);
		}
		if (!redirect_fd(file, STDOUT_FILENO))
			return (EXIT_FAILURE);
		redir_out = redir_out->next;
	}
	return (EXIT_SUCCESS);
}
