/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   exit.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/08/24 22:08:43 by sreerink      #+#    #+#                 */
/*   Updated: 2024/09/30 02:49:42 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	exit_valid_arg(char *arg)
{
	size_t	i;

	i = 0;
	if (arg[0] == '-' || arg[0] == '+')
		i++;
	if (!arg[i])
		return (false);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (false);
		i++;
	}
	return (true);
}

int	exit_builtin(t_cmd *cmd, t_data *data)
{
	int	exit_status;

	exit_status = data->exit_status;
	if (data && data->process == 1)
		write(STDERR_FILENO, "exit\n", 5);
	if (cmd->args[1] && exit_valid_arg(cmd->args[1]))
	{
		if (cmd->args[2])
		{
			write(STDERR_FILENO, "minishell: exit: too many arguments\n", 36);
			return (1);
		}
		exit_status = ft_atoi(cmd->args[1]) % 256;
	}
	else if (cmd->args[1])
	{
		write(STDERR_FILENO, "minishell: exit: ", 17);
		write(STDERR_FILENO, cmd->args[1], ft_strlen(cmd->args[1]));
		write(STDERR_FILENO, ": numeric argument required\n", 28);
		exit_status = 2;
	}
	free_all(data);
	exit(exit_status);
}
