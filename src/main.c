/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                            :+:    :+:             */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/14 18:40:07 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/13 20:08:27 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_data	*init_shell(char **env_copy)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->env = copy_env(env_copy);
	data->input = NULL;
	data->list = NULL;
	data->process = 1;
	data->exit_status = 0;
	init_shlvl(data);
	// signals
	return (data);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	char	*input;

	(void)argc;
	(void)argv;
	data = init_shell(env);
	while (1)
	{
		input = readline(SHELL_NAME);
		if (!input)
			error_exit("readline", EXIT_FAILURE);
		data->input = input;
		if (input[0] != '\0')
			add_history(data->input);
		tokenize_and_expand(data);
		// print_linked_list(data->list);
		// print_commands(data->cmd_process);
		data->exit_status = make_processes(data);
		free_all(data);
	}
	return (0);
}
