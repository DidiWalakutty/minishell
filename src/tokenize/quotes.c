/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/20 16:40:02 by diwalaku      #+#    #+#                 */
/*   Updated: 2023/12/05 16:02:28 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// checks if the char is a quote
// or a non-token.
int	quote_length(char *str, char c)
{
	int	i;

	i = 0;
	if (c == '\'' || c == '\"')
	{
		while (str[i] && str[i] != c)
		{
			printf("str[%i] is: %c\n", i, str[i]);
			i++;
		}
		return (i);
	}
}

static int	count_quotes(char *str, int i, int *quote_nb, char q)
{
	*quote_nb += 1;
	i++;
	while (str[i])
	{
		if (str[i] == q)
		{
			*quote_nb += 1;
			break ;
		}
		i++;
	}
	return (i);
}

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
			i += count_quotes(str, i, &single_q, '\'');
		else if (str[i] == '\"')
			i += count_quotes(str, i, &double_q, '\"');
		i++;
	}
	if (single_q % 2 != 0 || double_q % 2 != 0)
	{
		ft_printf("Unclosed quotes detected\n");
		return (false);
	}
	return (true);
}

void	skip_quotedstring(char *str, int *i)
{
	if (str[*i] == '\'')
	{
		*i += 1;
		while (str[*i] && str[*i] != '\'')
			*i += 1;
		if (str[*i] == '\'')
			*i += 1;
	}
	else if (str[*i] == '\"')
	{
		*i += 1;
		while (str[*i] && str[*i] != '\"')
			*i += 1;
		if (str[*i] == '\"')
			*i += 1;
	}
}
