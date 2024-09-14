/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   nia_signals.c                                     :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/09/13 17:50:26 by sreerink      #+#    #+#                 */
/*   Updated: 2024/09/14 21:22:42 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	nia_sigint_handler(int sig)
{
	write(STDERR_FILENO, "\n", 1);
}

void	nia_sigquit_handler(int sig)
{
	write(STDERR_FILENO, "Quit (core dumped)\n", 19);
}

void	set_signals_nia_mode(t_data *data)
{
	enable_echoctl();
	data->sa_int.sa_handler = &nia_sigint_handler;
	sigemptyset(&data->sa_int.sa_mask);
	data->sa_int.sa_flags = 0;
	sigaction(SIGINT, &data->sa_int, NULL);
	data->sa_quit.sa_handler = &nia_sigquit_handler;
	sigemptyset(&data->sa_quit.sa_mask);
	data->sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &data->sa_quit, NULL);
}
