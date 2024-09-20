/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   ia_signals.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/09/13 17:50:16 by sreerink      #+#    #+#                 */
/*   Updated: 2024/09/18 23:00:26 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ia_sigint_handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	write(STDERR_FILENO, "\n^C\n", 4);
	rl_on_new_line();
	rl_redisplay();
}

void	ia_sigquit_handler(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
}

void	set_signals_ia_mode(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	disable_echoctl();
	sa_int.sa_handler = &ia_sigint_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = &ia_sigquit_handler;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
