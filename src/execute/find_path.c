/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   find_path.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/09/26 20:54:26 by sreerink      #+#    #+#                 */
/*   Updated: 2024/10/01 17:40:44 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	cleanup_find_path(char *slash_cmd, char **path_arr)
{
	free(slash_cmd);
	free_array(path_arr);
}

static char	**split_path_env(t_cmd *cmd, t_data *data)
{
	size_t	i;
	char	**path_arr;

	i = 0;
	while (cmd->env[i] && ft_strncmp(cmd->env[i], "PATH=", 5))
		i++;
	if (!cmd->env[i] || !cmd->env[i][5])
		return (NULL);
	path_arr = ft_split(cmd->env[i] + 5, ':');
	if (!path_arr)
		error_exit("ft_split", EXIT_FAILURE, data);
	return (path_arr);
}

static char	*check_cmd_is_path(t_cmd *cmd, t_data *data)
{
	if (access(cmd->cmd, F_OK) != 0)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		error_exit(cmd->cmd, 1127, data);
	}
	return (cmd->cmd);
}

static char	*check_paths_cmd(char *cmd, char **path_arr, t_data *data)
{
	size_t	i;
	char	*path_temp;
	int		access_check;

	i = 0;
	access_check = 1;
	path_temp = NULL;
	while (access_check != 0 && path_arr[i])
	{
		free(path_temp);
		path_temp = ft_strjoin(path_arr[i], cmd);
		if (!path_temp)
		{
			cleanup_find_path(cmd, path_arr);
			error_exit("ft_strjoin", EXIT_FAILURE, data);
		}
		access_check = access(path_temp, F_OK);
		i++;
	}
	if (access_check != 0)
	{
		free(path_temp);
		path_temp = NULL;
	}
	return (path_temp);
}

char	*find_cmd_path(t_cmd *cmd, t_data *data)
{
	char	*path;
	char	*slash_cmd;
	char	**path_arr;

	if (!ft_strncmp(cmd->cmd, "./", 2) || !ft_strncmp(cmd->cmd, "/", 1))
		return (cmd->cmd);
	if (!*cmd->cmd)
		error_exit(cmd->cmd, 127, data);
	path_arr = split_path_env(cmd, data);
	if (!path_arr)
		return (check_cmd_is_path(cmd, data));
	slash_cmd = ft_strjoin("/", cmd->cmd);
	if (!slash_cmd)
	{
		cleanup_find_path(NULL, path_arr);
		error_exit("ft_strjoin", EXIT_FAILURE, data);
	}
	path = check_paths_cmd(slash_cmd, path_arr, data);
	if (!path)
	{
		cleanup_find_path(slash_cmd, path_arr);
		error_exit(cmd->cmd, 127, data);
	}
	return (path);
}
