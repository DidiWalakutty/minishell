/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   cd.c                                              :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/08/04 22:34:30 by sreerink      #+#    #+#                 */
/*   Updated: 2024/08/17 01:00:11 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	get_cur_pwd(char buffer[PATH_MAX + 1])
{
	if (!getcwd(buffer, PATH_MAX + 1))
	{
		perror("minishell: cd_builtin: pwd");
		return (false);
	}
	return (true);
}

// Vraag aan Didi of "" wordt aangeleverd als NULL of "\0" voor cd ""
static char	*check_cd_args(t_cmd *cmd)
{
	char	*temp;

	if (!cmd->args[1])
		return (copy_env_input(cmd->env, "HOME"));
	else if (cmd->args[2])
	{
		write(STDERR_FILENO, "minishell: cd: too many arguments\n", 34);
		return (NULL);
	}
	else if (!strncmp("-", cmd->args[1], 2))
	{
		temp = copy_env_input(cmd->env, "OLDPWD");
		printf("%s\n", temp);
		return (temp);
	}
	return (cmd->args[1]);
}

int	cd_builtin(t_cmd *cmd)
{
	char	*path;
	char	temp[PATH_MAX + 1];

	if (!get_cur_pwd(temp))
		return (EXIT_FAILURE);
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
	if (!replace_env_var(temp, "OLDPWD=", cmd->env) || !get_cur_pwd(temp))
		return (EXIT_FAILURE);
	if (!replace_env_var(temp, "PWD=", cmd->env))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
