/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                         :+:    :+:             */
/*                                                     +:+                    */
/*   By: sreerink <sreerink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/02 21:44:34 by sreerink      #+#    #+#                 */
/*   Updated: 2024/09/14 22:26:58 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	redirect_heredoc(int pipe_hdoc[2], bool redirect)
{
	if (redirect)
	{
		if (!redirect_fd(pipe_hdoc[0], STDIN_FILENO))
		{
			close(pipe_hdoc[1]);
			return (false);
		}
	}
	else
		close(pipe_hdoc[0]);
	close(pipe_hdoc[1]);
	return (true);
}

bool		heredoc(t_redin *redir_in, bool redirect)
{
	int		pipe_hdoc[2];
	char	*input;

	if (pipe(pipe_hdoc) == -1)
		return (false);
	input = readline("> ");
	while (input && strncmp(input, redir_in->str, ft_strlen(redir_in->str) + 1))
	{
		write(pipe_hdoc[1], input, ft_strlen(input));
		write(pipe_hdoc[1], "\n", 1);
		free(input);
		input = readline("> ");
	}
	if (!input)
	{
		write(STDERR_FILENO, "minishell: warning: here-document del", 37);
		write(STDERR_FILENO, "imited by end-of-file (wanted `", 31);
		write(STDERR_FILENO, redir_in->str, ft_strlen(redir_in->str));
		write(STDERR_FILENO, "')\n", 3);
	}
	if (!redirect_heredoc(pipe_hdoc, redirect))
		return (false);
	free(input);
	return (true);
}
