/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   builtins.c                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/08/04 18:46:29 by sreerink      #+#    #+#                 */
/*   Updated: 2024/09/30 01:52:07 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_builtin(t_cmd *cmd, t_data *data)
{
	int		exit_status;

	exit_status = 0;
	if (cmd->builtin == CD)
		exit_status = cd_builtin(cmd, data);
	else if (cmd->builtin == ECHO_BUILTIN)
		exit_status = echo_builtin(cmd);
	else if (cmd->builtin == PWD)
		exit_status = pwd_builtin();
	else if (cmd->builtin == EXPORT)
		exit_status = export_builtin(cmd, data);
	else if (cmd->builtin == UNSET)
		exit_status = unset_builtin(cmd, data);
	else if (cmd->builtin == ENV)
		exit_status = env_builtin(cmd->env);
	else if (cmd->builtin == EXIT)
		exit_status = exit_builtin(cmd, data);
	return (exit_status);
}
