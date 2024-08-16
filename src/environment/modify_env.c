/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   modify_env.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/08/17 00:13:39 by sreerink      #+#    #+#                 */
/*   Updated: 2024/08/17 00:13:41 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	replace_env_var(char *new_value, char *var_dst, char **env)
{
	size_t	i;
	size_t	var_len;

	i = 0;
	var_len = ft_strlen(var_dst);
	while (env[i] && strncmp(env[i], var_dst, var_len))
		i++;
	if (!env[i])
		return (false);
	free(env[i]);
	env[i] = ft_strjoin(var_dst, new_value);
	if (!env[i])
		return (false);
	return (true);
}
