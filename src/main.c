/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/14 18:40:07 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/07/29 18:56:38 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// isatty checks if the standard input is pointing to our terminal,
// still needs to have a quit_program function.
// Copies env, unsets old PWD and increments shlvl.
// Sets all variables to NULL.
// Termcaps???
// process al op 1 ivm child
static t_data	*init_shell(char **env_copy)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	// if (!isatty(STDIN_FILENO))
	// 	exit_program();
	data->env = env_copy;
	data->input = NULL;
	data->list = NULL;
	data->process = 1;
	// data->token = NULL; Not needed?
	// TODO: PATH's
	// TODO: unset old PWD
	// TODO: increment shlvl
	// signals
	return (data);
}

// what to do with exit_code $? exit-status???
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
			return (1);
		data->input = input;
		if (input != NULL)
			add_history(data->input);
		lexer_and_parser(data);
		printf("!!! After expanding:\n");
		print_linked_list(data->list);
		// build commands: concatenate 
		// executor();
		free_all(data);
	}
	return (0);
}
