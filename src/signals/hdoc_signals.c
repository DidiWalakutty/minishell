/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   hdoc_signals.c                                    :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/09/18 21:17:15 by sreerink      #+#    #+#                 */
/*   Updated: 2024/09/18 22:49:27 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	write(STDERR_FILENO, "\n^C\n", 4);
	exit(130);
}

void	heredoc_sigquit_handler(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
}

void	set_signals_hdoc_mode(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = &heredoc_sigint_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = &heredoc_sigquit_handler;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
