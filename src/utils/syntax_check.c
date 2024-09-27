/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_check.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/06 15:56:32 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/24 18:50:13 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_redir_syntax(char *str, int *i, bool *error_found)
{
	int	x;

	x = 0;
	*error_found = true;
	while (str[x])
		x++;
	if (str[x] == '|')
		return (error_msg("syntax error near unexpected token", \
				'|', '\0'));
	while (str[*i] == '<' || str[*i] == '>' || str[*i] == ' ' || str[*i] == '|')
	{
		if (str[*i] == '|')
			return (error_msg("syntax error near unexpected token", \
					'|', '\0'));
		(*i)++;
	}
	if (str[*i] == '\0')
	{
		return (error_msg("syntax error near unexpected token", \
			str[*i - 1], '\0'));
	}
	*error_found = false;
	return (0);
}

bool	only_whitespace(char *str, int *j)
{
	while (str[*j] && str[*j] == ' ')
		(*j)++;
	if (str[*j] == '\0')
		return (true);
	return (false);
}

bool	check_start(char *str, int *j, bool *error_found)
{
	if (only_whitespace(str, j) == true)
		return (true);
	if (str[*j] == '|')
	{
		*error_found = true;
		return (error_msg("syntax error near unexpected token", \
				str[*j], '\0'));
	}
	else
	{
		if (check_redir_syntax(str, j, error_found))
			return (error_found);
	}
	return (false);
}

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

bool	check_syntax_errors(char *str)
{
	int		i;
	bool	error_found;

	i = 0;
	error_found = false;
	if (str[i] == ' ' || str[i] == '|' || str[i] == '<' || str[i] == '>')
		if (check_start(str, &i, &error_found) == true)
			return (error_found);
	while (str[i])
	{
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
