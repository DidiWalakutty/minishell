/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_heredocs.c                                  :+:    :+:             */
/*                                                     +:+                    */
/*   By: sreerink <sreerink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/08 19:46:52 by sreerink      #+#    #+#                 */
/*   Updated: 2024/09/17 22:39:49 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_heredocs(t_data *data)
{
	t_cmd	*temp;
	t_redin	*redir_in;

	temp = data->cmd_process;
	while (temp)
	{
		redir_in = temp->redir_in;
		while (redir_in)
		{
			if (redir_in->heredoc && !redir_in->next)
			{
				if (pipe(temp->redir_in->pipe_hdoc) == -1)
					return (false);
				heredoc(temp->redir_in, true);
			}
			else if (redir_in->heredoc)
				heredoc(temp->redir_in, false);
			redir_in = redir_in->next;
		}
		temp = temp->next;
	}
	return (true);
}
