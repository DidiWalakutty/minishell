/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/14 18:42:29 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/08/23 16:47:15 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token		*tokenize_input(t_data *data, char *str);
static bool	check_syntax_errors(char *str);
static bool	token_syntax_error(char *str, int *i);

// Check for syntax errors, tokenizes, expands
// and builds commands.
int	tokenizer_and_parser(t_data *data)
{
	if (!data)
		return (1);
	if (check_syntax_errors(data->input) == true)
		return (1);
	if ((all_quotes_closed(data->input) == false))
		return (1);
	data->list = tokenize_input(data, data->input);
	expand_input(data, data->list, data->env);
	print_linked_list(data->list);
	data->cmd_process = build_commands(data->list, data);
	return (0);
}

// Checks the string for syntax errors.
static bool	check_syntax_errors(char *str)
{
	int		i;
	bool	error_found;

	i = 0;
	error_found = false;
	skip_whitespace(str, &i);
	if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		if (check_start(str, &i) == false);
			return (true);
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
		if (str[i] && str[i] != '\'' && str[i] != '\"')
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
			return (error_msg("syntax error near unexpected token", \
					str[*i], '\0'));
	}
	if (str[*i] == '<' || str[*i] == '>')
	{
		(*i)++;
		if (str[*i] == str[*i - 1])
			(*i)++;
		skip_whitespace(str, i);
		if (str[*i] == '<' || str[*i] == '>' || \
			str[*i] == '|' || str[*i] == '\0')
			return (error_msg("syntax error near unexpected token", \
					str[*i], '\0'));
	}
	return (false);
}

static int	add_space(char *str, int i, t_token **list)
{
	t_token	*new;
	char	*line;

	line = ft_strdup(" ");
	new = create_node(line, SEPARATOR);
	node_to_list(list, new);
	while (iswhitespace(str[i]))
		i++;
	return (i);
}

// Tokenizes input into nodes.
// currently iterates beyond the \0.
t_token	*tokenize_input(t_data *data, char *str)
{
	int		i;
	t_token	*list;

	i = 0;
	list = NULL;
	if (!str)
		return (create_node(NULL, EMPTY));
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
