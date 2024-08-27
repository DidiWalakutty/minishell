/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   shlvl.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/08/25 22:49:38 by sreerink      #+#    #+#                 */
/*   Updated: 2024/08/27 19:02:38 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	increment_shlvl(int new_shlvl, char **env)
{
	char	*shlvl_str;

	shlvl_str = ft_itoa(new_shlvl);
	if (!shlvl_str)
		return (false);
	if (!replace_var_value(shlvl_str, "SHLVL=", env))
	{
		free(shlvl_str);
		return (false);
	}
	free(shlvl_str);
	return (true);
}

bool	init_shlvl(t_data *data)
{
	size_t	i;
	int		shlvl_int;

	i = 0;
	while (data->env[i])
	{
		if (!strncmp(data->env[i], "SHLVL=", 6))
		{
			if (!increment_shlvl(atoi(data->env[i] + 6) + 1, data->env))
				return (false);
			return (true);
		}
		i++;
	}
	data->env = make_env_var("SHLVL=", "1", data->env);
	if (!data->env)
		return (false);
	return (true);
}
