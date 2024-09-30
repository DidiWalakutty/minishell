/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sreerink <sreerink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/27 18:06:24 by sreerink      #+#    #+#                 */
/*   Updated: 2024/09/30 20:47:41 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	errno_to_exit_status(int err)
{
	if (err == ENOENT)
		return (127);
	else if (err == EACCES)
		return (126);
	return (EXIT_FAILURE);
}

static void	child_process(t_cmd *cmd, int fd_in[], int fd_out[], t_data *data)
{
	if (!redirect_input(cmd, fd_in))
	{
		close(fd_out[0]);
		close(fd_out[1]);
		error_exit(NULL, EXIT_FAILURE, data);
	}
	if (!redirect_output(cmd, fd_out))
		error_exit(NULL, EXIT_FAILURE, data);
	if (cmd->builtin)
		error_exit(NULL, execute_builtin(cmd, data), data);
	cmd->path = find_cmd_path(cmd, data);
	execve(cmd->path, cmd->args, cmd->env);
	error_exit(cmd->cmd, errno_to_exit_status(errno), data);
}

static void	fork_and_execute(int **pipefd, t_data *data)
{
	size_t	i;
	t_cmd	*cmd;

	i = 0;
	cmd = data->cmd_process;
	while (cmd)
	{
		cmd->pid = fork();
		if (cmd->pid == -1)
			error_exit("minishell: fork", EXIT_FAILURE, data);
		if (cmd->pid == 0)
		{
			close_pipes_heredoc(data->cmd_process, i);
			close_unused_pipes(pipefd, i, data->process + 1);
			child_process(cmd, pipefd[i], pipefd[i + 1], data);
		}
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		cmd = cmd->next;
		i++;
	}
	close(pipefd[i][0]);
	close(pipefd[i][1]);
	close_pipes_heredoc(data->cmd_process, -1);
}

static int	wait_childs(t_cmd *cmds)
{
	int	status;
	int	exit_status;

	while (cmds)
	{
		waitpid(cmds->pid, &status, 0);
		cmds = cmds->next;
	}
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			exit_status = 130;
		if (WTERMSIG(status) == SIGQUIT)
			exit_status = 131;
	}
	return (exit_status);
}

void	execute(t_data *data)
{
	int		status;

	if (!data->cmd_process)
		return ;
	status = check_heredocs(data);
	if (status != 0)
	{
		data->exit_status = status;
		return ;
	}
	if (check_parent_builtin(data))
		return ;
	set_signals_nia_mode();
	data->pipefd = alloc_pipefd(data);
	make_pipes(data->pipefd, data);
	fork_and_execute(data->pipefd, data);
	data->exit_status = wait_childs(data->cmd_process);
}
