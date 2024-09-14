/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   ia_signals.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/09/13 17:50:16 by sreerink      #+#    #+#                 */
/*   Updated: 2024/09/14 22:03:28 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ia_sigint_handler(int sig)
{
	rl_replace_line("", 0);
	write(STDERR_FILENO, "\n^C\n", 4);
	rl_on_new_line();
	rl_redisplay();
}

void	ia_sigquit_handler(int sig)
{
	rl_on_new_line();
	rl_redisplay();
}

void	set_signals_ia_mode(t_data *data)
{
	if (!disable_echoctl())
		error_exit(NULL, EXIT_FAILURE);
	data->sa_int.sa_handler = &ia_sigint_handler;
	sigemptyset(&data->sa_int.sa_mask);
	sigaction(SIGINT, &data->sa_int, NULL);
	data->sa_quit.sa_handler = &ia_sigquit_handler;
	sigemptyset(&data->sa_quit.sa_mask);
	sigaction(SIGQUIT, &data->sa_quit, NULL);
}
