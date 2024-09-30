/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                         :+:    :+:             */
/*                                                     +:+                    */
/*   By: sreerink <sreerink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/02 21:44:34 by sreerink      #+#    #+#                 */
/*   Updated: 2024/09/30 23:49:51 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	hdoc_error_msg(t_redin *redir_in)
{
	write(STDERR_FILENO, "minishell: warning: here-document del", 37);
	write(STDERR_FILENO, "imited by end-of-file (wanted `", 31);
	write(STDERR_FILENO, redir_in->str, ft_strlen(redir_in->str));
	write(STDERR_FILENO, "')\n", 3);
}

static void	write_hdoc_pipe(char *input, t_redin *redir_in, t_data *data)
{
/*	char	*expanded;

	if (!redir_in->quotes)
	{
		expanded = expand_hdoc(input);
		write(redir_in->pipe_hdoc[1], expanded, ft_strlen(expanded));
		write(redir_in->pipe_hdoc[1], "\n", 1);
		free(expanded);
	}*/
	write(redir_in->pipe_hdoc[1], input, ft_strlen(input));
	write(redir_in->pipe_hdoc[1], "\n", 1);
}

void	heredoc(t_redin *redir_in, bool redirect, t_data *data)
{
	char	*input;

	set_signals_hdoc_mode();
	input = readline("> ");
	while (input && strncmp(input, redir_in->str, ft_strlen(redir_in->str) + 1))
	{
		if (redirect)
			write_hdoc_pipe(input, redir_in, data);
		free(input);
		input = readline("> ");
	}
	if (!input)
		hdoc_error_msg(redir_in);
	if (redirect)
	{
		close(redir_in->pipe_hdoc[0]);
		close(redir_in->pipe_hdoc[1]);
	}
	free(input);
	if (data)
		free_all(data);
	exit(0);
}
