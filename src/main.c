/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                            :+:    :+:             */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/20 16:40:26 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/07/03 22:54:54 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_exit(void)
{
	printf("Inside error_exit\n");
}

t_cmd	*init_cmd_node(t_cmd *cmds, char *str, char **args, char **envp)
{
	t_cmd	*head;
	t_cmd	*last;
	t_cmd	*new;

	head = cmds;
	last = head;
	while (last && last->next)
		last = last->next;
	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		error_exit();
	new->cmd = str;
	new->args = args;
	new->env = envp;
	if (head == NULL)
		return (new);
	last->next = new;
	return (head);
}

int	main(int argc, char *argv[], char *envp[])
{
	size_t	i;
	char	*str[] = {"echo", "ls"};
	char	***args;
	t_data	*data;

	i = 0;
	argc = 0;
	argv[0] = "Yo";
	args[0][0] = "echo";
	args[0][1] = "hello";
	args[0][2] = "\0";
	data = ft_calloc(1, sizeof(t_data));
	data->pipe_num = 1;
	while (i < data->pipe_num)
	{
		data->cmd_process = init_cmd_node(data->cmd_process, str[i], args[i], envp);
		i++;
	}
	return (make_processes(data));
}
