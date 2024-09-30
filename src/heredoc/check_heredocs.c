/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_heredocs.c                                  :+:    :+:             */
/*                                                     +:+                    */
/*   By: sreerink <sreerink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/08 19:46:52 by sreerink      #+#    #+#                 */
/*   Updated: 2024/09/30 01:21:44 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	run_heredoc(t_redin *redir_in, bool redirect, t_data *data)
{
	pid_t	pid;
	int		status;

	if (redirect)
	{
		if (pipe(redir_in->pipe_hdoc) == -1)
			return (1);
	}
	pid = fork();
	if (pid == 0)
		heredoc(redir_in, redirect, data);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

static int	check_hdoc_redir(t_redin *redir_in, t_data *data)
{
	int		status;

	while (redir_in)
	{
		if (redir_in->heredoc && !redir_in->next)
		{
			status = run_heredoc(redir_in, true, data);
			if (status != 0)
				return (status);
		}
		else if (redir_in->heredoc)
		{
			status = run_heredoc(redir_in, false, data);
			if (status != 0)
				return (status);
		}
		redir_in = redir_in->next;
	}
	return (0);
}

int	check_heredocs(t_data *data)
{
	int		status;
	t_cmd	*temp;

	set_signals_hdoc_parent_mode();
	temp = data->cmd_process;
	while (temp)
	{
		status = check_hdoc_redir(temp->redir_in, data);
		if (status != 0)
			return (status);
		temp = temp->next;
	}
	return (0);
}
