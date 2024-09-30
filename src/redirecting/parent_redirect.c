/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parent_redirect.c                                 :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/09/27 19:40:40 by sreerink      #+#    #+#                 */
/*   Updated: 2024/09/30 00:33:54 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirect_input_parent(t_redin *redir_in)
{
	int	file;

	if (!redir_in)
		return (EXIT_SUCCESS);
	if (redirect_redir_in(redir_in) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	redirect_output_parent(t_redou *redir_out)
{
	int	file;

	if (!redir_out)
		return (EXIT_SUCCESS);
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
		if (!redir_out->next)
		{
			if (!redirect_fd(file, STDOUT_FILENO))
				return (EXIT_FAILURE);
		}
		else
			close(file);
		redir_out = redir_out->next;
	}
	return (EXIT_SUCCESS);
}
