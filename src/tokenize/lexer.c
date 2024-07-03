/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                           :+:    :+:             */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/20 16:39:51 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/06/12 20:26:00 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	check_syntax_errors(char *str);
t_node	*tokenize_input(t_data *data, char *str);
static bool	token_syntax_error(char *str, int *i);

// This function checks if there are any syntax errors in the given string
// and if all quotes are closed.
// We then tokenize the input.
int	lexer(t_data *data)
{
	t_node	*temp;

	if (!data)
		return (1);
	if (check_syntax_errors(data->input) == true)
	{
		free(data->input);
		return (1);
	}
	if ((all_quotes_closed(data->input) == false))
		return (1);
	temp = tokenize_input(data, data->input);
	return (0);
}

// Checks the string for syntax errors.
static bool	check_syntax_errors(char *str)
{
	int	i;

	i = 0;
	skip_whitespace(str, &i);
	if (str[i] == '|')
		return (error_msg("syntax error near unexpected token", str[i]));
	while (str[i])
	{
		skip_to_token(str, &i);
		if (str[i] == '\'' || str[i] == '\"')
			skip_quotedstring(str, &i);
		else if (str[i])
		{
			if (token_syntax_error(str, &i) == true)
				return (true);
		}
		i++;
	}
	return (false);
}

// When |, it's next token can't be a | or \0.
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

static void	print_linked_list(t_node *head)
{
    while (head != NULL)
    {
        printf("Node is: %s - type is: %s \n", head->str, type_to_string(head->type));
        head = head->next;
    }
    printf("\n");
}

// Tokenizes input into nodes.
// currently iterates beyond the \0.
// For |; Just pipes, right? Not |&?
t_node	*tokenize_input(t_data *data, char *str)
{
	t_node	*list;
	int		i;

	i = 0;
	list = NULL;
	if (!str)
		return (create_node(NULL));
	while (iswhitespace(str[i]))
		i++;
	while (str[i])
	{
		while (iswhitespace(str[i]))
			i++;
		if (str[i] == '\'')
			i = add_quote(str, i, '\'', &list);
		else if (str[i] == '\"')
			i = add_quote(str, i, '\"', &list);
		else if (str[i] == '<' || str[i] == '>')
			i = add_redir(str, i, str[i], &list);
		else if (str[i] == '|')
		{
			i = add_one_token(str, i, str[i], &list);
			data->pipe_num += 1;
		}
		else
			i = add_word(str, i, &list);
	}
	printf("\nprint list:\n");
	print_linked_list(list);
	return (list);
}
