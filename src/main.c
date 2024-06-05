/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/20 16:40:26 by diwalaku      #+#    #+#                 */
/*   Updated: 2023/12/05 20:28:23 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static void	init_shell(t_data *data)
{
	data->input = NULL;
	data->list = NULL;
	data->token = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	*input;

	// check argc
	(void)argc;
	(void)argv;
	data.env = copy_env(env);
	int i = 0;
	// Check if env is copied.
	while (data.env[i])
	{
		printf("env_list[i] is: %s\n", data.env[i]);
		i++;
	}
	while (1)
	{
		init_shell(&data); // TODO: Set tools to NULL or false, PATH + pwd
		prompt(&data); // prompt + history. strtrim gives leaks!
		input = readline(SHELL_NAME);
		if (!input) // check for [0]?
			exit_error("exit");
		data.input = input;
		if (input != NULL)
			add_history(data.input);
		lexer(&data);
		// expanding: check for $
		// build commands: concatenate 
		// parsing();
		// executor();
		//free(data->input);
	}
	return (0);
}
