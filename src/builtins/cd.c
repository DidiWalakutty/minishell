/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   cd.c                                              :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/08/04 22:34:30 by sreerink      #+#    #+#                 */
/*   Updated: 2024/08/24 21:37:16 by sreerink      ########   odam.nl         */
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
	{
		temp = copy_env_input(cmd->env, "HOME");
		if (!temp)
			write(STDERR_FILENO, "minishell: cd: HOME not set\n", 28);
	}
	else if (cmd->args[2])
	{
		write(STDERR_FILENO, "minishell: cd: too many arguments\n", 34);
		return (NULL);
	}
	else if (!strncmp("-", cmd->args[1], 2))
	{
		temp = copy_env_input(cmd->env, "OLDPWD");
		if (!temp)
			write(STDERR_FILENO, "minishell: cd: OLDPWD not set\n", 30);
		else
			printf("%s\n", temp);
	}
	else
		temp = cmd->args[1];
	return (temp);
}

static bool	update_cd_vars(char *old_pwd, t_data *data)
{
	char	cur_pwd[PATH_MAX + 1];

	if (!data)
		return (true);
	if (!replace_var_value(old_pwd, "OLDPWD=", data->env))
	{
		data->env = make_env_var("OLDPWD=", old_pwd, data->env);
		if (!data->env)
		{
			perror("minishell: cd_builtin: make_env_var");
			return (false);
		}
	}
	if (!get_cur_pwd(cur_pwd))
		return (false);
	if (!replace_var_value(cur_pwd, "PWD=", data->env))
	{
		data->env = make_env_var("PWD=", cur_pwd, data->env);
		if (!data->env)
		{
			perror("minishell: cd_builtin: make_env_var");
			return (false);
		}
	}
	return (true);
}

int	cd_builtin(t_cmd *cmd, t_data *data)
{
	char	*path;
	char	old_pwd[PATH_MAX + 1];

	if (!get_cur_pwd(old_pwd))
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
	if (!update_cd_vars(old_pwd, data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
