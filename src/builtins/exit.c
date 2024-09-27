/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   exit.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/08/24 22:08:43 by sreerink      #+#    #+#                 */
/*   Updated: 2024/09/27 16:16:51 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exit_builtin(t_cmd *cmd, t_data *data)
{
	int	exit_status;

	exit_status = 0;
	if (data && data->process == 1)
		write(STDERR_FILENO, "exit\n", 5);
	if (cmd->args[1] && str_is_all_digits(cmd->args[1]))
	{
		if (cmd->args[2])
		{
			write(STDERR_FILENO, "minishell: exit: too many arguments\n", 36);
			return (1);
		}
		exit_status = atoi(cmd->args[1]) % 256; // Replace with Libft function
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
