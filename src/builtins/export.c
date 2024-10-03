/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   export.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/08/27 19:22:55 by sreerink      #+#    #+#                 */
/*   Updated: 2024/10/03 22:40:00 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	parse_export_arg(char *arg, char **result, size_t i)
{
	size_t	len;

	len = i;
	if (arg[i - 1] == '+')
	{
		if (!arg[i + 1])
			result[2] = NULL;
		result[0] = "+";
		len = i - 1;
	}
	result[1] = ft_strndup(arg, len);
	if (!result[1])
		return (false);
	if (arg[i + 1])
	{
		result[2] = ft_strdup(arg + i + 1);
		if (!result[2])
			return (false);
	}
	return (true);
}

static size_t	export_check_chars(char *arg)
{
	size_t	i;

	i = 1;
	if (ft_isdigit(arg[0]) || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (0);
	while (arg[i])
	{
		if (arg[i] == '=')
			return (i);
		if (!is_alph_or_num(arg[i]) && arg[i] != '_')
		{
			if (arg[i] == '+' && arg[i + 1] == '=')
				return (i + 1);
			return (0);
		}
		i++;
	}
	return (0);
}

static char	**check_export_arg(char *arg)
{
	char	**result;
	size_t	i;

	result = ft_calloc(3, sizeof(char *));
	if (!result)
		return (NULL);
	i = export_check_chars(arg);
	if (i == 0)
	{
		free(result);
		return (export_error_msg(arg));
	}
	if (!parse_export_arg(arg, result, i))
	{
		free(result[1]);
		free(result[2]);
		free(result);
		return (NULL);
	}
	return (result);
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
		while (!ft_strncmp(variable, data->env[i], ft_strlen(variable)))
		{
			if (export_args[0])
				add_var_value(export_args[2], variable, cmd->env);
			else
				replace_var_value(export_args[2], variable, cmd->env);
			free(variable);
			return ;
		}
		i++;
	}
	if (data)
		data->env = make_env_var(variable, export_args[2], data->env);
	else
		cmd->env = make_env_var(variable, export_args[2], cmd->env);
	free(variable);
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
		export_args = check_export_arg(cmd->args[i]);
		if (!export_args)
			return (EXIT_FAILURE);
		update_env_export(export_args, cmd, data);
		export_args[0] = NULL;
		free(export_args[1]);
		free(export_args[2]);
		free(export_args);
		if ((data && !data->env) || !cmd->env)
		{
			perror("minishell: export_builtin");
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
