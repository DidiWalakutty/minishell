/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   pipes.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/06/12 20:30:41 by sreerink      #+#    #+#                 */
/*   Updated: 2024/08/07 20:47:34 by sreerink      ########   odam.nl         */
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

void	redirect_input(t_cmd *cmd, int fd_in[], int fd_out[])
{
	int file;

	close(fd_in[1]);
	if (!cmd->redirect_in)
	{
		close(fd_in[0]);
	}
	// Following line needs to be replaced with a Libft function
	else if (!strcmp(cmd->redirect_in, "|"))
	{
		if (dup2(fd_in[0], STDIN_FILENO) == -1)
			error_exit("dup2", EXIT_FAILURE);
		close(fd_in[0]);
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
		if (dup2(file, STDIN_FILENO) == -1)
			error_exit("dup2", EXIT_FAILURE);
		close(file);
	}
}

void	redirect_output(t_cmd *cmd, int fd_in[], int fd_out[])
{
	int	file;

	close(fd_out[0]);
	if (!cmd->redirect_out)
		close(fd_out[1]);
	// Following line needs to be replaced with a Libft function
	else if (!strcmp(cmd->redirect_out, "|"))
	{
		if (dup2(fd_out[1], STDOUT_FILENO) == -1)
			error_exit("dup2", EXIT_FAILURE);
		close(fd_out[1]);
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
		if (dup2(file, STDOUT_FILENO) == -1)
			error_exit("dup2", EXIT_FAILURE);
		close(file);
	}
}

void	child_process(t_cmd *cmd, int fd_in[], int fd_out[])
{
	redirect_input(cmd, fd_in, fd_out);
	redirect_output(cmd, fd_in, fd_out);
	if (cmd->builtin)
		error_exit(NULL, execute_builtin(cmd));
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
