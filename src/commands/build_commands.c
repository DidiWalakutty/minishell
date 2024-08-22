/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build_commands.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/22 18:14:06 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/08/22 22:40:23 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	handle_redirect(t_token *token, t_cmd *command, t_data *data)
// {
// 	t_type	type;

// 	type = token->type;
// 	token = token->next;
// 	if (token->type == SEPARATOR)
// 		token = token->next;
// 	if (type == REDIR_OUT || type == APPEND)
// 		command->outfile = token->str;
// 	else
// 		command->infile = token->str;
// }

static void	add_to_array(char **new_array, char **arguments, char *str)
{
	int	i;

	i = 0;
	while (arguments[i])
	{
		new_array[i] = ft_strdup(arguments[i]);
		if (!new_array[i])
			free_array(new_array);
		i++;
	}
	
}

char	**add_to_double_array(char **arguments, char *str)
{
	int		i;
	char	**new_array;

	i = 0;
	if (!str && !arguments)
		return (NULL);
	if (!str)
		return (arguments);
	while (arguments[i])
		i++;
	if (str)
		new_array = malloc(sizeof(char *) * (i + 2));
	else
		new_array = malloc(sizeof(char *) * (i + 1));
	if (!new_array)
		return (NULL);
	add_to_array(new_array, arguments, str);
	return (new_array);
}

void	set_command(t_token *token, t_cmd *commands, t_cmd_var *var)
{
	if (var->command == NULL)
	{
		if (token->type == WORD || token->type == SINGLE_QUOTE || \
			token->type == DOUBLE_QUOTE)
			var->command = token->str;
	}
	else
	{
		if (token->type == PIPE)
		{
			// push it to command;
			printf("Pipe found\n");
		}
		else
		{
			var->arguments = add_to_double_array(var->arguments, token->str);
		}
	}
}		

// if (a_redirection(tokens->type) == true)
		// {
		// 	if (handle_redirect(&tokens, &commands, data) == 1)
		// 		printf("check for failure and free");
		// }

t_cmd_var	*init_tracker(void)
{
	t_cmd_var	*tracker;

	tracker = malloc(sizeof(t_cmd_var));
	tracker->command = NULL;
	tracker->arguments = NULL;
	return (tracker);
}

t_cmd	*merge_commands(t_token *tokens, t_data *data)
{
	t_cmd		*commands;
	t_cmd_var	*tracker;
	// variable to hold args?

	// init_args_tracker?
	tracker = init_tracker();
	commands = NULL;
	while (tokens)
	{
		// if (a_redirection(tokens->type) == true)
		// {
		// 	if (handle_redirect(&tokens, &commands, data) == 1)
		// 		printf("check for failure and free");
		// }
		set_command(&tokens, &commands, &tracker);
		tokens = tokens->next;
	}
	return (commands);
}

t_cmd	*build_commands(t_token *tokens, t_data *data)
{
	t_cmd		*commands;

	commands = NULL;
	if (tokens && not_just_spaces(tokens))
	{
		commands = merge_commands(tokens, data);
		// if (!commands)
			printf("free things\n");
		// handle_them
	}
	return (commands);
}
