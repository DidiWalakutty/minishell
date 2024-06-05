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

// Set all variable to NULL.
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

	(void)argc;
	(void)argv;
	data.env = copy_env(env);
	while (1)
	{
		// !!! TODO: Currently needs to receive input twice, before going into lexer.
		init_shell(&data); // TODO: Set PATH + pwd
		// prompt_shellname(&data); // Not necessary if we use line below.
		input = readline(SHELL_NAME); // No need to fix *readline*-leaks.
		if (!input)
			return (1);
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

// !!! Check if env is copied. !!!
// int i = 0;
// while (data.env[i])
// {
// 	printf("env_list[i] is: %s\n", data.env[i]);
// 	i++;
// }