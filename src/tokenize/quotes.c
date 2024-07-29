/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/14 18:43:00 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/07/28 19:25:07 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// checks for the length of the add_quote node,
// searches for the closing quote.
int	quote_length(char *str, char c)
{
	int	i;

	i = 0;
	if (c == '\'' || c == '\"')
	{
		while (str[i] && str[i] != c)
			i++;
		return (i);
	}
	return (i);
}

// Only checks for the closing given quote.
// If it encounters the non-given quote, it'll iterate over it, since
// it has no value between the given quotes.
static int	count_quotes(char *str, int i, int *quote_nb, char q)
{
	*quote_nb += 1;
	i++;
	while (str[i])
	{
		if (str[i] == q)
		{
			*quote_nb += 1;
			return (i);
		}
		i++;
	}
	return (i - 1);
}

// Checks if all quotes in the string are properly closed.
// Keeps track of the number 
bool	all_quotes_closed(char *str)
{
	int	i;
	int	single_q;
	int	double_q;

	i = 0;
	single_q = 0;
	double_q = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\'')
			i = count_quotes(str, i, &single_q, '\'');
		else if (str[i] == '\"')
			i = count_quotes(str, i, &double_q, '\"');
		i++;
	}
	if (single_q % 2 != 0 || double_q % 2 != 0)
	{
		ft_printf("Unclosed quotes detected\n");
		return (false);
	}
	return (true);
}

// Checks if the quoted string is closed with the same quote.
// CHECK: Return at end of function should return true (error is found),
// because if it doesn't 
// go into either return statements of the if-loops, it's still an error???
bool	skip_quotedstring(char *str, int *i)
{
	char	quote_type;

	quote_type = str[*i];
	if (str[*i] == '\'' || str[*i] == '\"')
	{
		(*i)++;
		while (str[*i] && str[*i] != quote_type)
			(*i)++;
		if (str[*i] == quote_type)
		{
			(*i)++;
			return (false);
		}
		else
			return (error_msg("syntax error: missing closing quote", str[*i]));
	}
	return (true);
}
