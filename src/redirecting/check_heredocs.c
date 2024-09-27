/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_heredocs.c                                  :+:    :+:             */
/*                                                     +:+                    */
/*   By: sreerink <sreerink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/08 19:46:52 by sreerink      #+#    #+#                 */
/*   Updated: 2024/09/26 19:18:35 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_heredocs_parent(t_redin *redir_in)
{
	while (redir_in)
	{
		if (redir_in->heredoc && !redir_in->next)
		{
			if (pipe(redir_in->pipe_hdoc) == -1)
				return (false);
			heredoc(redir_in, true, NULL);
		}
		else if (redir_in->heredoc)
			heredoc(redir_in, false, NULL);
		redir_in = redir_in->next;
	}
	return (true);
}

int	check_heredocs(t_data *data)
{
	pid_t	pid;
	int		status;
	t_cmd	*temp;
	t_redin	*redir_in;

	set_signals_hdoc_parent_mode();
	temp = data->cmd_process;
	while (temp)
	{
		redir_in = temp->redir_in;
		while (redir_in)
		{
			if (redir_in->heredoc && !redir_in->next)
			{
				if (pipe(redir_in->pipe_hdoc) == -1)
					return (1);
				pid = fork();
				if (pid == 0)
					heredoc(redir_in, true, data);
				waitpid(pid, &status, 0);
				if (status != 0)
					return (WEXITSTATUS(status));
			}
			else if (redir_in->heredoc)
			{
				pid = fork();
				if (pid == 0)
					heredoc(redir_in, false, data);
				waitpid(pid, &status, 0);
				if (status != 0)
					return (WEXITSTATUS(status));
			}
			redir_in = redir_in->next;
		}
		temp = temp->next;
	}
	return (0);
}
