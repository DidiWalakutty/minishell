/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                           :+:    :+:             */
/*                                                     +:+                    */
/*   By: sreerink <sreerink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/12 20:30:41 by sreerink      #+#    #+#                 */
/*   Updated: 2024/09/30 00:06:39 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_unused_pipes(int **pipefd, size_t cur_pipe, size_t total_pipes)
{
	size_t	i;

	i = 0;
	while (i < total_pipes)
	{
		if (i != cur_pipe && i != cur_pipe + 1)
		{
			close(pipefd[i][0]);
			close(pipefd[i][1]);
		}
		i++;
	}
}

void	close_pipes_heredoc(t_cmd *cmd, ssize_t cur_cmd)
{
	ssize_t	i;
	t_redin	*redir_in;

	i = 0;
	if (i == cur_cmd)
		cmd = cmd->next;
	while (cmd)
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
		if (i == cur_cmd)
			cmd = cmd->next->next;
		else
			cmd = cmd->next;
	}
}

void	free_pipefd_allocs(t_data *data)
{
	size_t	i;

	if (!data->pipefd)
		return ;
	i = 0;
	while (i < data->process + 1)
	{
		free(data->pipefd[i]);
		i++;
	}
	free(data->pipefd);
	data->pipefd = NULL;
}

int	**alloc_pipefd(t_data *data)
{
	size_t	i;
	int		**pipefd;

	i = 0;
	pipefd = malloc((data->process + 1) * sizeof(int *));
	if (!pipefd)
		error_exit("malloc", EXIT_FAILURE, data);
	while (i < data->process + 1)
	{
		pipefd[i] = malloc(2 * sizeof(int));
		if (!pipefd[i])
		{
			data->process = i + 1;
			error_exit("malloc", EXIT_FAILURE, data);
		}
		i++;
	}
	return (pipefd);
}

void	make_pipes(int **pipefd, t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->process + 1)
	{
		if (pipe(pipefd[i]) == -1)
			error_exit("minishell: pipe", EXIT_FAILURE, data);
		i++;
	}
}
