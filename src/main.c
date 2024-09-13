/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                            :+:    :+:             */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/14 18:40:07 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/13 23:50:31 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	disable_echoctl(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		perror("tcgetattr");
		return (false);
	}
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDERR_FILENO, TCSANOW, &term) == -1)
	{
		perror("tcsetattr");
		return (false);
	}
	return (true);
}

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
	return (data);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	char	*input;

	(void)argc;
	(void)argv;
	if (!disable_echoctl())
		return (EXIT_FAILURE);
	data = init_shell(env);
	set_signals_ia_mode(data);
	while (1)
	{
		input = readline(SHELL_NAME);
		if (!input)
		{
			// Will be changed to a proper exit function (Purpose: Ctrl-D)
			write(STDERR_FILENO, "exit\n", 5);
			exit(data->exit_status);
		}
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
