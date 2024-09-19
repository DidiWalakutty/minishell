/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/14 18:42:29 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/13 19:59:17 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Checks for syntax errors.
// Expands input and builds commands.
int	tokenize_and_expand(t_data *data)
{
	if (!data)
		return (1);
	if (check_syntax_errors(data->input) == true)
		return (1);
	if ((all_quotes_closed(data->input) == false))
		return (1);
	data->list = tokenize_input(data, data->input);
	expand_input(data, data->list, data->env);
	data->cmd_process = build_commands(data->list, data);
	return (0);
}

// Tokenizes input into nodes.
// currently iterates beyond the \0.
t_token	*tokenize_input(t_data *data, char *str)
{
	int		i;
	t_token	*list;

	i = 0;
	list = NULL;
	while (iswhitespace(str[i]))
		i++;
	while (str[i])
	{
		if (str[i] == '\'')
			i = add_quote(str, i, '\'', &list);
		else if (str[i] == '\"')
			i = add_quote(str, i, '\"', &list);
		else if (iswhitespace(str[i]))
			i = add_space(str, i, &list);
		else if (str[i] == '<' || str[i] == '>' || str[i] == '|')
			i = add_redir_or_pipe(str, i, data, &list);
		else
			i = add_word(str, i, &list);
	}
	return (list);
}
