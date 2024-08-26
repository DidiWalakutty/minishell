/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   unset.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/08/26 19:15:16 by sreerink      #+#    #+#                 */
/*   Updated: 2024/08/26 21:57:46 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	unset_builtin(t_cmd *cmd, t_data *data)
{
	size_t	i;

	i = 1;
	while (cmd->args[i])
	{
		if (data)
			data->env = delete_env_var(cmd->args[i], data->env);
		else
			cmd->env = delete_env_var(cmd->args[i], cmd->env);
		i++;
	}
	return (EXIT_SUCCESS);
}
