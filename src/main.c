/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                            :+:    :+:             */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/14 18:40:07 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/10/01 02:12:33 by sreerink      ########   odam.nl         */
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
	data->cmd_process = NULL;
	data->pipefd = NULL;
	data->process = 1;
	data->exit_status = 0;
	init_shlvl(data);
	return (data);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	data = init_shell(env);
	if (!data)
		error_exit("malloc", EXIT_FAILURE, NULL);
	while (1)
	{
		set_signals_ia_mode();
		data->input = readline(SHELL_NAME);
		if (!data->input)
			exit_end_of_file(data);
		if (*data->input)
			add_history(data->input);
		expand_and_build(data);
		execute(data);
		reset_data(data);
	}
	return (0);
}
