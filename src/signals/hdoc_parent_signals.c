/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   hdoc_parent_signals.c                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/09/18 22:50:28 by sreerink      #+#    #+#                 */
/*   Updated: 2024/09/18 23:07:46 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	hdoc_parent_sigint_handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
}

void	hdoc_parent_sigquit_handler(int sig)
{
	(void)sig;
}

void	set_signals_hdoc_parent_mode(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = &hdoc_parent_sigint_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = &hdoc_parent_sigquit_handler;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
