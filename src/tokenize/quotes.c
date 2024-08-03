/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/14 18:43:00 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/08/03 21:25:49 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
		printf("Unclosed quotes detected\n");
		return (false);
	}
	return (true);
}

bool	skip_quotedstring(char *str, int *i)
{
	char	quote_type;

	quote_type = str[*i];
	(*i)++;
	while (str[*i])
	{
		if (str[*i] == quote_type)
		{
			(*i)++;
			return (false);
		}
		(*i)++;
	}
	return (error_msg("syntax error: missing closing quote", quote_type));
}
