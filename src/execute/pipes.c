/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   pipes.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/06/12 20:30:41 by sreerink      #+#    #+#                 */
/*   Updated: 2024/07/03 22:46:23 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_exit(char	*msg, int status)
{
	if (msg)
		perror(msg);
	exit(status);
}

void	child_process(t_cmd *cmd, int pipefd[])
{
	int	file1;
	int	file2;

	if (!cmd->redirect_in)
		close(pipefd[0]);
	// Following line needs to be replaced with a Libft function
	else if (!strcmp(cmd->redirect_in, "|"))
	{
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			error_exit("dup2", EXIT_FAILURE);
		close(pipefd[0]);
	}
	else
	{
		close(pipefd[0]);
		file1 = open(cmd->redirect_in, O_RDONLY);
		if (file1 == -1)
			error_exit(cmd->redirect_in, EXIT_FAILURE);
		if (dup2(file1, STDIN_FILENO) == -1)
			error_exit("dup2", EXIT_FAILURE);
		close(file1);
	}
	// Under following line is all redirecting output
	// TO DO: separate redirect in/output into functions
	// -----------------------------------------------------
	if (!cmd->redirect_out)
		close(pipefd[1]);
	// Following line needs to be replaced with a Libft function
	else if (!strcmp(cmd->redirect_out, "|"))
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			error_exit("dup2", EXIT_FAILURE);
		close(pipefd[1]);
	}
	else
	{
		close(pipefd[1]);
		file2 = open(cmd->redirect_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file2 == -1)
			error_exit(cmd->redirect_out, EXIT_FAILURE);
		if (dup2(file2, STDOUT_FILENO) == -1)
			error_exit("dup2", EXIT_FAILURE);
		close(file2);
	}
	execve(cmd->path, cmd->args, cmd->env);
}

int	make_processes(t_data *data)
{
	size_t	i;
	t_cmd	*cmds;
	t_cmd	*temp;
	int		status;
	int		pipefd[data->pipe_num][2];

	i = 0;
	cmds = data->cmd_process;
	temp = cmds;
	while (i < data->pipe_num)
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
			child_process(temp, pipefd[i]);
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		temp = temp->next;
		i++;
	}
	temp = cmds;
	while (temp)
	{
		if (waitpid(temp->pid, &status, 0) == -1)
			error_exit("waitpid", EXIT_FAILURE);
		temp = temp->next;
	}
	return (WEXITSTATUS(status));
}
