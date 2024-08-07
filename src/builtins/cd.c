/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   cd.c                                              :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/08/04 22:34:30 by sreerink      #+#    #+#                 */
/*   Updated: 2024/08/07 21:38:04 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Vraag aan Didi of "" wordt aangeleverd als NULL of "\0" voor cd ""
static char	*check_cd_args(t_cmd *cmd)
{
	if (!cmd->args[1])
		return (copy_env_input(cmd->env, "HOME"));
	else if (cmd->args[2])
	{
		write(STDERR_FILENO, "minishell: cd: too many arguments\n", 34);
		return (NULL);
	}
	return (cmd->args[1]);
}

int	cd_builtin(t_cmd *cmd)
{
	char	*path;

	path = check_cd_args(cmd);
	if (!path)
		return (EXIT_FAILURE);
	if (chdir(path) == -1)
	{
		write(STDERR_FILENO, "minishell: cd: ", 15);
		perror(path);
		if (path != cmd->args[1])
			free(path);
		return (EXIT_FAILURE);
	}
	if (path != cmd->args[1])
		free(path);
	return (EXIT_SUCCESS);
}
