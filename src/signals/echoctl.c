/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   echoctl.c                                         :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/09/14 00:57:48 by sreerink      #+#    #+#                 */
/*   Updated: 2024/09/14 00:57:51 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	enable_echoctl(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		perror("tcgetattr");
		return ;
	}
	term.c_lflag |= ECHOCTL;
	if (tcsetattr(STDERR_FILENO, TCSANOW, &term) == -1)
		perror("tcsetattr");
}
