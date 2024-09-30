/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_heredocs.c                                  :+:    :+:             */
/*                                                     +:+                    */
/*   By: sreerink <sreerink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/08 19:46:52 by sreerink      #+#    #+#                 */
/*   Updated: 2024/10/01 01:01:41 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	close_pipes_hdoc_child(t_cmd *cmd, size_t cur_cmd)
{
	size_t	i;
	t_redin	*redir_in;

	i = 1;
	while (i != cur_cmd)
	{
		redir_in = cmd->redir_in;
		while (redir_in)
		{
			if (redir_in->heredoc && !redir_in->next)
			{
				close(redir_in->pipe_hdoc[0]);
				close(redir_in->pipe_hdoc[1]);
			}
			redir_in = redir_in->next;
		}
		i++;
		cmd = cmd->next;
	}
}

static int	run_heredoc(t_redin *redir_in, bool redir, size_t i, t_data *data)
{
	pid_t	pid;
	int		status;

	if (redir)
	{
		if (pipe(redir_in->pipe_hdoc) == -1)
			return (1);
	}
	pid = fork();
	if (pid == 0)
	{
		close_pipes_hdoc_child(data->cmd_process, i);
		heredoc(redir_in, redir, data);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

static int	check_hdoc_redir(t_redin *redir_in, size_t i, t_data *data)
{
	int		status;

	while (redir_in)
	{
		if (redir_in->heredoc && !redir_in->next)
		{
			status = run_heredoc(redir_in, true, i, data);
			if (status != 0)
				return (status);
		}
		else if (redir_in->heredoc)
		{
			status = run_heredoc(redir_in, false, i, data);
			if (status != 0)
				return (status);
		}
		redir_in = redir_in->next;
	}
	return (0);
}

int	check_heredocs(t_data *data)
{
	size_t	i;
	int		status;
	t_cmd	*temp;

	set_signals_hdoc_parent_mode();
	i = 1;
	temp = data->cmd_process;
	while (temp)
	{
		status = check_hdoc_redir(temp->redir_in, i, data);
		if (status != 0)
			return (status);
		i++;
		temp = temp->next;
	}
	return (0);
}
