/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sreerink <sreerink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/02 21:44:34 by sreerink      #+#    #+#                 */
/*   Updated: 2024/09/12 19:06:16 by diwalaku      ########   odam.nl         */
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
	while (strncmp(input, redir_in->str, ft_strlen(redir_in->str) + 1))
	{
		write(pipe_hdoc[1], input, ft_strlen(input));
		write(pipe_hdoc[1], "\n", 1);
		free(input);
		input = readline("> ");
	}
	if (!redirect_heredoc(pipe_hdoc, redirect))
		return (false);
	if (!input)
		return (false);
	free(input);
	return (true);
}
