/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   modify_env.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/08/17 00:13:39 by sreerink      #+#    #+#                 */
/*   Updated: 2024/08/24 21:39:41 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**make_env_var(char *new_var, char *value, char **env)
{
	char	**new_env;
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	new_env = ft_calloc(i + 2, sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			return (NULL); // return (free_array(new_env));
		i++;
	}
	if (value)
		new_env[i] = ft_strjoin(new_var, value);
	else
		new_env[i] = ft_strdup(new_var);
	if (!new_env[i])
		return (NULL); // return (free_array(new_env));
	// free_array(env); (Oude data->env wordt misschien niet corrrect ge-freed)
	return (new_env);
}

bool	replace_var_value(char *new_value, char *var_dst, char **env)
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
