/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   export.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/08/27 19:22:55 by sreerink      #+#    #+#                 */
/*   Updated: 2024/09/02 18:59:04 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	export_print_env(char **env)
{
	size_t	i;

	i = 0;
	while (env && env[i])
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

static char	**parse_export_arg(char *arg)
{
	size_t	i;
	size_t	len;
	char	**result;

	i = 0;
	result = ft_calloc(3, sizeof(char *));
	if (!result)
		return (NULL);
	while (arg[i])
	{
		if (arg[i] == '=')
		{
			len = i;
			if (i == 0 || (!is_alph_or_num(arg[i - 1]) && arg[i - 1] != '+'))
			{
				write(STDERR_FILENO, "minishell: export: `", 20);
				write(STDERR_FILENO, arg, ft_strlen(arg));
				write(STDERR_FILENO, "': not a valid identifier\n", 26);
				return (NULL);
			}
			if (arg[i - 1] == '+')
			{
				if (!arg[i + 1])
					result[2] = NULL;
				result[0] = "+";
				len = i - 1;
			}
			result[1] = ft_strndup(arg, len);
			if (!result[1])
				return (NULL);
			if (arg[i + 1])
			{
				result[2] = ft_strdup(arg + i + 1);
				if (!result[2])
					return (NULL);
			}
			return (result);
		}
		i++;
	}
	return (NULL);
}

static void	update_env_export(char **export_args, t_cmd *cmd, t_data *data)
{
	size_t	i;
	char	*variable;

	i = 0;
	variable = ft_strjoin(export_args[1], "=");
	if (!variable)
		return ;
	while (data->env[i])
	{
		while (!strncmp(variable, data->env[i], ft_strlen(variable)))
		{
			if (export_args[0])
				add_var_value(export_args[2], variable, cmd->env);
			else
				replace_var_value(export_args[2], variable, cmd->env);
			return ;
		}
		i++;
	}
	if (data)
		data->env = make_env_var(variable, export_args[2], data->env);
	else
		cmd->env = make_env_var(variable, export_args[2], cmd->env);
}

int	export_builtin(t_cmd *cmd, t_data *data)
{
	size_t	i;
	char	**export_args;

	i = 1;
	if (!cmd->args[1])
		return (export_print_env(cmd->env));
	while (cmd->args[i])
	{
		export_args = parse_export_arg(cmd->args[i]);
		if (!export_args)
			return (EXIT_FAILURE);
		update_env_export(export_args, cmd, data);
		if ((data && !data->env) || !cmd->env)
		{
			perror("minishell: export_builtin");
			return (EXIT_FAILURE);
		}
		export_args[0] = NULL;
		free(export_args[1]);
		free(export_args[2]);
		free(export_args);
		i++;
	}
	return (EXIT_SUCCESS);
}