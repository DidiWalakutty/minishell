/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   builtins.c                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/08/04 18:46:29 by sreerink      #+#    #+#                 */
/*   Updated: 2024/08/04 18:50:25 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_builtin(t_cmd *cmd)
{
	printf("Inside execute_builtin()\n");
	if (cmd->builtin == ECHO)
		echo_builtin(cmd);
	else if (cmd->builtin == PWD)
		pwd_builtin();
	exit(EXIT_SUCCESS);
}
