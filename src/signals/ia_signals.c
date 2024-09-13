/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   ia_signals.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/09/13 17:50:16 by sreerink      #+#    #+#                 */
/*   Updated: 2024/09/14 00:08:24 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ia_sigquit_handler(int sig)
{
	rl_on_new_line();
	rl_redisplay();
}

void	set_signals_ia_mode(t_data *data)
{
	data->sa_quit.sa_handler = &ia_sigquit_handler;
	sigemptyset(&data->sa_quit.sa_mask);
	data->sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &data->sa_quit, NULL);
}
