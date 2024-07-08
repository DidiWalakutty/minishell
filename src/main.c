/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                            :+:    :+:             */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/20 16:40:26 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/07/08 21:03:06 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_exit(char	*msg, int status)
{
	if (msg)
		perror(msg);
	exit(status);
}

t_cmd	*init_cmd_node(t_cmd *cmds, char *str, char **args, char **envp, char *in, char *out)
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
		error_exit("ft_calloc", EXIT_FAILURE);
	new->cmd = str;
	new->args = args;
	new->redirect_in = in;
	new->redirect_out = out;
	new->env = envp;
	if (head == NULL)
		return (new);
	last->next = new;
	return (head);
}

int	main(int argc, char *argv[], char *envp[])
{
	size_t	i;
	char	**args = malloc(sizeof(char *) * 3);
	char	**args2 = malloc(sizeof(char *) * 3);
	t_data	*data;

	i = 0;
/*	argc = 0;
	argv[0] = "Yo";
	args[0] = ft_strdup("cat");
	args[1] = ft_strdup("Makefile");
	args[2] = NULL;
	args2[0] = ft_strdup("cat");
	args2[1] = NULL;
	data = ft_calloc(1, sizeof(t_data));
	data->pipe_num = 2;
	data->cmd_process = init_cmd_node(data->cmd_process, args[0], args, envp, NULL, "|");
	data->cmd_process = init_cmd_node(data->cmd_process, args2[0], args2, envp, "|", NULL);
	return (make_processes(data));*/
	if (argc > 1)
		echo_builtin(argv[1], true);
	return (0);
}
