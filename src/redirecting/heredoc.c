/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   heredoc.c                                         :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/09/02 21:44:34 by sreerink      #+#    #+#                 */
/*   Updated: 2024/09/05 21:32:35 by sreerink      ########   odam.nl         */
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

bool	heredoc(t_cmd *cmd, bool redirect)
{
	int		pipe_hdoc[2];
	char	*input;

	if (pipe(pipe_hdoc) == -1)
		return (false);
	input = readline("> ");
	while (strncmp(input, cmd->redirect_in, ft_strlen(cmd->redirect_in) + 1))
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
