/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   modify_env.c                                        :+:    :+:           */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/08/17 00:13:39 by sreerink      #+#    #+#                 */
/*   Updated: 2024/10/03 15:28:57 by diwalaku       ########   odam.nl        */
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
			return (free_array(new_env), NULL);
		i++;
	}
	if (value)
		new_env[i] = ft_strjoin(new_var, value);
	else
		new_env[i] = ft_strdup(new_var);
	if (!new_env[i])
		return (free_array(new_env), NULL);
	free_array(env);
	return (new_env);
}

char	**delete_env_var(char *del_var, char **env)
{
	char	**new_env;
	size_t	i;
	size_t	j;

	i = 0;
	while (env[i])
		i++;
	new_env = ft_calloc(i + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], del_var, ft_strlen(del_var)))
		{
			new_env[j] = ft_strdup(env[i]);
			if (!new_env[j])
				return (free_array(new_env), NULL);
			j++;
		}
		i++;
	}
	free_array(env);
	return (new_env);
}

bool	add_var_value(char *new_value, char *var_dst, char **env)
{
	size_t	i;
	size_t	var_len;
	char	*var_temp;

	i = 0;
	var_len = ft_strlen(var_dst);
	while (env[i] && ft_strncmp(env[i], var_dst, var_len))
		i++;
	if (!env[i])
		return (false);
	var_temp = ft_strdup(env[i]);
	if (!var_temp)
		return (false);
	free(env[i]);
	env[i] = ft_strjoin(var_temp, new_value);
	free(var_temp);
	if (!env[i])
		return (false);
	return (true);
}

bool	replace_var_value(char *new_value, char *var_dst, char **env)
{
	size_t	i;
	size_t	var_len;

	i = 0;
	var_len = ft_strlen(var_dst);
	while (env[i] && ft_strncmp(env[i], var_dst, var_len))
		i++;
	if (!env[i])
		return (false);
	free(env[i]);
	if (new_value)
		env[i] = ft_strjoin(var_dst, new_value);
	else
		env[i] = ft_strdup(var_dst);
	if (!env[i])
		return (false);
	return (true);
}
