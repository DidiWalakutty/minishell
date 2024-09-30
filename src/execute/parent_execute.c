/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parent_execute.c                                  :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/09/27 19:30:17 by sreerink      #+#    #+#                 */
/*   Updated: 2024/09/30 00:32:03 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	dup_stdin_stdout(int std_fd[2])
{
	std_fd[0] = dup(STDIN_FILENO);
	if (std_fd[0] == -1)
	{
		perror("dup");
		return (-1);
	}
	std_fd[1] = dup(STDOUT_FILENO);
	if (std_fd[1] == -1)
	{
		perror("dup");
		close(std_fd[0]);
		return (-1);
	}
	return (0);
}

static int	redirect_parent(t_cmd *cmd, int std_fd[2])
{
	if (redirect_input_parent(cmd->redir_in) == 1)
	{
		close(std_fd[0]);
		close(std_fd[1]);
		return (-1);
	}
	if (redirect_output_parent(cmd->redir_out) == 1)
	{
		close(std_fd[0]);
		close(std_fd[1]);
		return (-1);
	}
	return (0);
}

static void	redirect_std_back(t_cmd *cmd, int std_fd[2], t_data *data)
{
	if (cmd->redir_in)
	{
		if (!redirect_fd(std_fd[0], STDIN_FILENO))
		{
			close(std_fd[1]);
			error_exit(NULL, EXIT_FAILURE, data);
		}
	}
	if (cmd->redir_out)
	{
		if (!redirect_fd(std_fd[1], STDOUT_FILENO))
			error_exit(NULL, EXIT_FAILURE, data);
	}
}

static int	builtin_in_parent(t_cmd *cmd, t_data *data)
{
	int	std_fd[2];
	int	exit_status;

	if (dup_stdin_stdout(std_fd) == -1)
		return (EXIT_FAILURE);
	if (redirect_parent(cmd, std_fd) == -1)
		return (EXIT_FAILURE);
	exit_status = execute_builtin(cmd, data);
	redirect_std_back(cmd, std_fd, data);
	close(std_fd[0]);
	close(std_fd[1]);
	return (exit_status);
}

bool	check_parent_builtin(t_data *data)
{
	if (data->cmd_process->builtin && data->process == 1)
	{
		data->exit_status = builtin_in_parent(data->cmd_process, data);
		return (true);
	}
	return (false);
}
