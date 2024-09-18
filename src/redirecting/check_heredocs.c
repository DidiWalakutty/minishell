/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_heredocs.c                                  :+:    :+:             */
/*                                                     +:+                    */
/*   By: sreerink <sreerink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/08 19:46:52 by sreerink      #+#    #+#                 */
/*   Updated: 2024/09/18 23:20:58 by sreerink      ########   odam.nl         */
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
			heredoc(redir_in, true);
		}
		else if (redir_in->heredoc)
			heredoc(redir_in, false);
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

	temp = data->cmd_process;
	while (temp)
	{
		redir_in = temp->redir_in;
		while (redir_in)
		{
			printf("hdoc delim = %s\n", redir_in->str);
			if (redir_in->heredoc && !redir_in->next)
			{
				if (pipe(temp->redir_in->pipe_hdoc) == -1)
					return (1);
				pid = fork();
				if (pid == 0)
					heredoc(temp->redir_in, true);
				waitpid(pid, &status, 0);
				printf("hdoc redir done: %s\n", redir_in->str);
				if (status != 0)
					return (WEXITSTATUS(status));
			}
			else if (redir_in->heredoc)
			{
				pid = fork();
				if (pid == 0)
					heredoc(temp->redir_in, false);
				waitpid(pid, &status, 0);
				printf("hdoc non redir done: %s\n", redir_in->str);
				if (status != 0)
					return (WEXITSTATUS(status));
			}
			redir_in = redir_in->next;
		}
		temp = temp->next;
	}
	return (0);
}
