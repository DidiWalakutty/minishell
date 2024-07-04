/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diwalaku <diwalaku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:40:07 by diwalaku          #+#    #+#             */
/*   Updated: 2024/07/04 16:07:52 by diwalaku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// isatty checks if the standard input is pointing to our terminal,
// still needs to have a quit_program function.
// Copies env, unsets old PWD and increments shlvl.
// Sets all variables to NULL.
// Termcaps???
// process al op 1 ivm child
static void	init_shell(t_data *data, char **env)
{
	// if (!isatty(STDIN_FILENO))
	// 	exit_program();
	data->env = copy_env(env);
	data->input = NULL;
	data->list = NULL;
	data->token = NULL;
	data->process = 1;
	// TODO: PATH's
	// TODO: unset old PWD
	// TODO: increment shlvl
	// signals
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	*input;

	(void)argc;
	(void)argv;
	while (1)
	{
		init_shell(&data, env);
		input = readline(SHELL_NAME);
		if (!input)
			return (1);
		data.input = input;
		if (input != NULL)
			add_history(data.input);
		lexer_and_parser(&data);
		printf("In main after expanding:\n");
		print_linked_list(data.list);
		// build commands: concatenate 
		// executor();
		//free(data->input);
	}
	return (0);
}
