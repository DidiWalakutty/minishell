/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   pipes.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/06/12 20:30:41 by sreerink      #+#    #+#                 */
/*   Updated: 2024/08/24 21:21:57 by sreerink      ########   odam.nl         */
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

char	*find_cmd_path(t_cmd *cmd)
{
	size_t	i;
	char	**path_arr;
	char	*slash_cmd;
	char	*path_temp;
	int		access_check;

	i = 0;
	access_check = 1;
	if (!strncmp(cmd->cmd, "./", 2) || !strncmp(cmd->cmd, "/", 1))
		return (cmd->cmd);
	while (cmd->env[i] && strncmp(cmd->env[i], "PATH=", 5))
		i++;
	path_arr = ft_split(cmd->env[i] + 5, ':');
	if (!path_arr)
		error_exit("ft_split", EXIT_FAILURE);
	slash_cmd = ft_strjoin("/", cmd->cmd);
	if (!slash_cmd)
		error_exit("ft_strjoin", EXIT_FAILURE);
	i = 0;
	while (access_check != 0 && path_arr[i])
	{
		path_temp = ft_strjoin(path_arr[i], slash_cmd);
		access_check = access(path_temp, F_OK);
		i++;
	}
	if (access_check != 0)
		error_exit(cmd->cmd, 127);
	free(slash_cmd);
	// free_array(path_arr);
	return (path_temp);
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

void	redirect_input(t_cmd *cmd, int fd_in[], int fd_out[])
{
	int file;

	close(fd_in[1]);
	if (!cmd->redirect_in)
		close(fd_in[0]);
	// Following line needs to be replaced with a Libft function
	else if (!strcmp(cmd->redirect_in, "|"))
	{
		if (!redirect_fd(fd_in[0], STDIN_FILENO))
			error_exit(NULL, EXIT_FAILURE);
	}
	else
	{
		close(fd_in[0]);
		file = open(cmd->redirect_in, O_RDONLY);
		if (file == -1)
		{
			close(fd_out[0]);
			close(fd_out[1]);
			error_exit(cmd->redirect_in, EXIT_FAILURE);
		}
		if (!redirect_fd(file, STDIN_FILENO))
			error_exit(NULL, EXIT_FAILURE);
	}
}

void	redirect_output(t_cmd *cmd, int fd_out[])
{
	int	file;

	close(fd_out[0]);
	if (!cmd->redirect_out)
		close(fd_out[1]);
	// Following line needs to be replaced with a Libft function
	else if (!strcmp(cmd->redirect_out, "|"))
	{
		if (!redirect_fd(fd_out[1], STDOUT_FILENO))
			error_exit(NULL, EXIT_FAILURE);
	}
	else
	{
		close(fd_out[1]);
		if (cmd->append)
			file = open(cmd->redirect_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			file = open(cmd->redirect_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file == -1)
			error_exit(cmd->redirect_out, EXIT_FAILURE);
		if (!redirect_fd(file, STDOUT_FILENO))
			error_exit(NULL, EXIT_FAILURE);
	}
}

void	child_process(t_cmd *cmd, int fd_in[], int fd_out[])
{
	redirect_input(cmd, fd_in, fd_out);
	redirect_output(cmd, fd_out);
	if (cmd->builtin)
		error_exit(NULL, execute_builtin(cmd, NULL));
	cmd->path = find_cmd_path(cmd);
	execve(cmd->path, cmd->args, cmd->env);
	error_exit(cmd->cmd, errno_to_exit_status(errno));
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

int	redirect_input_parent(t_cmd *cmd)
{
	int file;

	if (!cmd->redirect_in)
		return (EXIT_SUCCESS);
	else
	{
		file = open(cmd->redirect_in, O_RDONLY);
		if (file == -1)
		{
			perror(cmd->redirect_in);
			return (EXIT_FAILURE);
		}
		if (!redirect_fd(file, STDIN_FILENO))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	redirect_output_parent(t_cmd *cmd)
{
	int	file;

	if (!cmd->redirect_out)
		return (EXIT_SUCCESS);
	else
	{
		if (cmd->append)
			file = open(cmd->redirect_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			file = open(cmd->redirect_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file == -1)
		{
			perror(cmd->redirect_out);
			return (EXIT_FAILURE);
		}
		if (!redirect_fd(file, STDOUT_FILENO))
			return (EXIT_FAILURE);
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
	if (redirect_input_parent(cmd) == 1)
	{
		close(stdin_fd);
		close(stdout_fd);
		return (EXIT_FAILURE);
	}
	if (redirect_output_parent(cmd) == 1)
	{

		close(stdin_fd);
		close(stdout_fd);
		return (EXIT_FAILURE);
	}
	exit_status = execute_builtin(cmd, data);
	if (cmd->redirect_in && !redirect_fd(stdin_fd, STDIN_FILENO))
	{
		close(stdout_fd);
		error_exit(NULL, EXIT_FAILURE);
	}
	if (cmd->redirect_out && !redirect_fd(stdout_fd, STDOUT_FILENO))
		error_exit(NULL, EXIT_FAILURE);
	close(stdin_fd);
	close(stdout_fd);
	return (exit_status);
}

int	make_processes(t_data *data)
{
	size_t	i;
	t_cmd	*cmds;
	t_cmd	*temp;
	int		status;
	int		pipefd[data->process + 1][2];

	i = 0;
	cmds = data->cmd_process;
	temp = cmds;
	if (temp->builtin && data->process == 1)
		return (builtin_in_parent(temp, data));
	while (i < data->process + 1)
	{
		if (pipe(pipefd[i]) == -1)
			error_exit("pipe", EXIT_FAILURE);
		i++;
	}
	i = 0;
	while (temp)
	{
		temp->pid = fork();
		if (temp->pid == -1)
			error_exit("fork", EXIT_FAILURE);
		else if (temp->pid == 0)
		{
			close_unused_pipes(pipefd, i, data->process + 1);
			child_process(temp, pipefd[i], pipefd[i + 1]);
		}
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		temp = temp->next;
		i++;
	}
	close(pipefd[i][0]);
	close(pipefd[i][1]);
	temp = cmds;
	while (temp)
	{
		if (waitpid(temp->pid, &status, 0) == -1)
			error_exit("waitpid", EXIT_FAILURE);
		temp = temp->next;
	}
	return (WEXITSTATUS(status));
}
