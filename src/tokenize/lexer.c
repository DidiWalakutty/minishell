/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/20 16:39:51 by diwalaku      #+#    #+#                 */
/*   Updated: 2023/12/05 16:58:39 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_syntax_errors(char *str);
t_node		*tokenize_input(char *str);
static bool	token_syntax_error(char *str, int *i);

// This function checks if all quotes are even/closed
// and if there are any syntax errors in the given string.
int	lexer(t_data *data)
{
	t_node	*temp;
	int		i;

	i = 0;
	if (!data)
		return (1);
	if (check_syntax_errors(data->input) == true)
	{
		free(data->input);
		return (1);
	}
	if ((all_quotes_closed(data->input) == false))
	{	
		printf("unclosed quote error\n");
		return (1);
	}
	temp = tokenize_input(data->input);
	return (0);
}

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

static bool	token_syntax_error(char *str, int *i)
{
	if (str[*i] == '|')
	{
		*i += 1;
		skip_whitespace(str, i);
		if (str[*i] == '|' || str[*i] == '\0')
			return (error_msg("syntax error near unexpected token", str[*i]));
	}
	if (str[*i] == '<' || str[*i] == '>')
	{
		*i += 1;
		if (str[*i] == str[*i - 1])
			*i += 1;
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
        printf("string is: %s, type is: %s | \n", head->str, type_to_string(head->type));
        head = head->next;
    }
    printf("\n");
}

// currently iterates beyond the \0.
t_node	*tokenize_input(char *str)
{
	int		i;
	t_node	*list;

	i = 0;
	list = NULL;
	if (!str)
		return (create_node(NULL));
	while (str[i])
	{
		printf("i at begin while loop is: %i\n", i);
		if (str[i] == '\'')
			i = add_quote(str, i, '\'', &list) - 1;
		else if (str[i] == '\"')
			i = add_quote(str, i, '\"', &list) - 1;
		else if (str[i] == '<' || str[i] == '>')
			i = add_redir(str, i, str[i], &list);
		else if (str[i] == '|')
			i = add_pipe(str, i, )
		else if (iswhitespace(str[i]))
			i = add_space(str, i, &list);
		else
			i = add_word(str, i, &list);
		// else if (str[i] == '$')	// add it as word and check for expansiona ($) after lexing.
		// 	i = add_dollar(str, i, &list);
		if (str[i] != '\0')
		{
			printf("str[%i] is: %c\n", i, str[i]);
			printf("it's not a NULL terminator\n");
			i++;
			printf("after i++: %i\n", i);
		}
	}
	printf("print list:\n");
	print_linked_list(list);
	printf("last i is %i\n", i);
	return (list);
}
