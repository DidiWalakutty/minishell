/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                           :+:    :+:             */
/*                                                     +:+                    */
/*   By: sreerink <sreerink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/12 20:30:41 by sreerink      #+#    #+#                 */
/*   Updated: 2024/09/27 16:28:22 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		errno_to_exit_status(int err)
{
	if (err == ENOENT)
		return (127);
	else if (err == EACCES)
		return (126);
	return (EXIT_FAILURE);
}

bool	redirect_fd(int fd, int fd_dst)
{
	if (dup2(fd, fd_dst) == -1)
	{
		close(fd);
		perror("dup2");
		return (false);
	}
	close(fd);
	return (true);
}

int		redirect_redir_in(t_redin *redir_in)
{
	int	file;

	while (redir_in)
	{
		if (!redir_in->heredoc)
		{
			file = open(redir_in->str, O_RDONLY);
			if (file == -1)
			{
				perror(redir_in->str);
				return (EXIT_FAILURE);
			}
			if (!redirect_fd(file, STDIN_FILENO))
				return (EXIT_FAILURE);
		}
		else if (!redir_in->next)
		{
			close(redir_in->pipe_hdoc[1]);
			if (!redirect_fd(redir_in->pipe_hdoc[0], STDIN_FILENO))
				return (EXIT_FAILURE);
		}
		redir_in = redir_in->next;
	}
	return (EXIT_SUCCESS);
}

int		redirect_redir_out(t_redou *redir_out)
{
	int	file;

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
		if (!redirect_fd(file, STDOUT_FILENO))
			return (EXIT_FAILURE);
		redir_out = redir_out->next;
	}
	return (EXIT_SUCCESS);
}

bool	redirect_input(t_cmd *cmd, int fd_in[])
{
	close(fd_in[1]);
	if (!cmd->redir_in && !cmd->pipe_in)
		close(fd_in[0]);
	else if (!cmd->redir_in && cmd->pipe_in)
	{
		if (!redirect_fd(fd_in[0], STDIN_FILENO))
			return (false);
	}
	else
	{
		close(fd_in[0]);
		if (redirect_redir_in(cmd->redir_in) == 1)
			return (false);
	}
	return (true);
}

bool	redirect_output(t_cmd *cmd, int fd_out[])
{
	close(fd_out[0]);
	if (!cmd->redir_out && !cmd->pipe_out)
		close(fd_out[1]);
	else if (!cmd->redir_out && cmd->pipe_out)
	{
		if (!redirect_fd(fd_out[1], STDOUT_FILENO))
			return (false);
	}
	else
	{
		close(fd_out[0]);
		if (redirect_redir_out(cmd->redir_out) == 1)
			return (false);
	}
	return (true);
}

void	child_process(t_cmd *cmd, int fd_in[], int fd_out[], t_data *data)
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
	error_exit(cmd->cmd, errno_to_exit_status(errno), NULL);
}

void	close_unused_pipes(int pipefd[][2], size_t cur_pipe, size_t total_pipes)
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

int	redirect_input_parent(t_redin *redir_in)
{
	int file;

	if (!redir_in)
		return (EXIT_SUCCESS);
	if (!check_heredocs_parent(redir_in))
		return (EXIT_FAILURE);
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

int	builtin_in_parent(t_cmd *cmd, t_data *data)
{
	int	stdin_fd;
	int	stdout_fd;
	int	exit_status;

	stdin_fd = dup(STDIN_FILENO);
	if (stdin_fd == -1)
	{
		perror("dup");
		return (EXIT_FAILURE);
	}
	stdout_fd = dup(STDOUT_FILENO);
	if (stdout_fd == -1)
	{
		perror("dup");
		close(stdin_fd);
		return (EXIT_FAILURE);
	}
	if (redirect_input_parent(cmd->redir_in) == 1)
	{
		close(stdin_fd);
		close(stdout_fd);
		return (EXIT_FAILURE);
	}
	if (redirect_output_parent(cmd->redir_out) == 1)
	{

		close(stdin_fd);
		close(stdout_fd);
		return (EXIT_FAILURE);
	}
	exit_status = execute_builtin(cmd, data);
	if (cmd->redir_in && !redirect_fd(stdin_fd, STDIN_FILENO))
	{
		close(stdout_fd);
		error_exit(NULL, EXIT_FAILURE, data);
	}
	if (cmd->redir_out && !redirect_fd(stdout_fd, STDOUT_FILENO))
		error_exit(NULL, EXIT_FAILURE, data);
	close(stdin_fd);
	close(stdout_fd);
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

static void	make_pipes(int pipefd[][2], t_data *data)
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

static void	fork_and_execute(int pipefd[][2], t_data *data)
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
	int		pipefd[data->process + 1][2];

	if (!data->cmd_process)
		return ;
	if (check_parent_builtin(data))
		return ;
	status = check_heredocs(data);
	if (status != 0)
	{
		data->exit_status = status;
		return ;
	}
	set_signals_nia_mode();
	make_pipes(pipefd, data);
	fork_and_execute(pipefd, data);
	data->exit_status = wait_childs(data->cmd_process);
}
