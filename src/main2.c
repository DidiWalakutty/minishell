/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/20 16:40:26 by diwalaku      #+#    #+#                 */
/*   Updated: 2023/12/12 19:22:09 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static void	init_shell(t_data *data)
{
	data->input = NULL;
	data->list = NULL;
	data->token = NULL;
}

char	*line_read(t_data *data)
{
	char	*new_line;

	new_line = readline(SHELL_NAME);
	if (!new_line)
		exit_error("exit");
	data->input = new_line;
	if (data->input != NULL)
		add_history(data->input);
	return (0);	
}

// check if *input is necessary for line_read.
int	main(int argc, char **argv, char **envp)
{
	t_data	*tokens;
	t_env	*env;
	char	*input;
	int		i;

	// check argc
	(void)argc;
	(void)argv;
	env = copy_env(envp, env); // check at Codam
	while (env_list[i])
	{
		printf("env_list[i] is: %s\n", env_list[i]);
		i++;
	}
	while (1)
	{
		init_shell(&tokens);
		input = line_read(&tokens);
		// data.input = input;
		tokens = lexer();
		expander(&data, env); // !!! @ HERE !!!
		// !!! check if i need other structs for expaning !!!
		// expanding: check for $

		// build commands: concatenate 
		// parsing();
		// executor();
		//free(data->input);
		// free env
	}
	return (0);
}
