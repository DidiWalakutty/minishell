/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/14 18:40:07 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/06/14 19:43:42 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

// Set all variable to NULL.
static void	init_shell(t_data *data)
{
	data->input = NULL;
	data->list = NULL;
	data->token = NULL;
	data->pipe_num = 0;
	// data->i = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	*input;

	(void)argc;
	(void)argv;
	data.env = copy_env(env);
	while (1)
	{
		init_shell(&data);
		input = readline(SHELL_NAME);
		if (!input)
			return (1);
		data.input = input;
		if (input != NULL)
			add_history(data.input);
		lexer(&data);
		// expander(data.token, data.env);
		// expanding: check for $ and replace in string
		// build commands: concatenate 
		// executor();
		//free(data->input);
	}
	return (0);
}

// !!! Check if env is copied. !!!
// int i = 0;
// while (data.env[i])
// {
// 	printf("env_list[i] is: %s\n", data.env[i]);
// 	i++;
// }