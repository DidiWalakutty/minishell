/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                         :+:    :+:             */
/*                                                     +:+                    */
/*   By: sreerink <sreerink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/02 21:44:34 by sreerink      #+#    #+#                 */
/*   Updated: 2024/09/17 22:08:56 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	heredoc(t_redin *redir_in, bool redirect)
{
	char	*input;

	input = readline("> ");
	while (input && strncmp(input, redir_in->str, ft_strlen(redir_in->str) + 1))
	{
		if (redirect)
		{
			write(redir_in->pipe_hdoc[1], input, ft_strlen(input));
			write(redir_in->pipe_hdoc[1], "\n", 1);
		}
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
	free(input);
}
