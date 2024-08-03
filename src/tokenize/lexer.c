/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/14 18:42:29 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/08/03 21:51:09 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node		*tokenize_input(t_data *data, char *str);
static bool	check_syntax_errors(char *str);
static bool	token_syntax_error(char *str, int *i);

// This function checks if there are any syntax errors in the given string
// and if all quotes are closed.
// We then tokenize the input.
int	lexer_and_parser(t_data *data)
{
	if (!data)
		return (1);
	if (check_syntax_errors(data->input) == true)
	{
		free(data->input);
		return (1);
	}
	if ((all_quotes_closed(data->input) == false))
		return (1);
	data->list = tokenize_input(data, data->input);
	expand_input(data, data->list, data->env);
	print_linked_list(data->list);
	return (0);
}

// Checks the string for syntax errors.
static bool	check_syntax_errors(char *str)
{
	int		i;
	bool	error_found;

	i = 0;
	error_found = false;
	if (str[i] == '|')
		return (error_msg("syntax error near unexpected token", str[i]));
	while (str[i])
	{
		skip_whitespace(str, &i);
		skip_to_token(str, &i);
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (skip_quotedstring(str, &i) == true)
				error_found = true;
		}
		else if (str[i])
		{
			if (token_syntax_error(str, &i) == true)
				return (true);
		}
		if (str[i] != '\'' && str[i] != '\"')
			i++;
	}
	return (error_found);
}

// Nothing behind | makes it a heredoc, TODO???
// When < or >, it checks if +1 is the same.
// Its next token can't be <, > or a |.
static bool	token_syntax_error(char *str, int *i)
{
	if (str[*i] == '|')
	{
		(*i)++;
		skip_whitespace(str, i);
		if (str[*i] == '|' || str[*i] == '\0')
			return (error_msg("syntax error near unexpected token", str[*i]));
	}
	if (str[*i] == '<' || str[*i] == '>')
	{
		(*i)++;
		if (str[*i] == str[*i - 1])
			(*i)++;
		skip_whitespace(str, i);
		if (str[*i] == '<' || str[*i] == '>' || \
			str[*i] == '|' || str[*i] == '\0')
			return (error_msg("syntax error near unexpected token", str[*i]));
	}
	return (false);
}

// Tokenizes input into nodes.
// currently iterates beyond the \0.
// For |; Just pipes, right? Not |&?
t_node	*tokenize_input(t_data *data, char *str)
{
	int		i;
	t_node	*list;

	i = 0;
	list = NULL;
	if (!str)
		return (create_node(NULL, EMPTY));
	while (str[i])
	{
		while (iswhitespace(str[i]))
		{
			i++;
			if (str[i] == '\0')
				return (list);
		}
		if (str[i] == '\'')
			i = add_quote(str, i, '\'', &list);
		else if (str[i] == '\"')
			i = add_quote(str, i, '\"', &list);
		else if (str[i] == '<' || str[i] == '>' || str[i] == '|')
			i = add_redir_or_pipe(str, i, data, &list);
		else
			i = add_word(str, i, &list);
	}
	return (list);
}
