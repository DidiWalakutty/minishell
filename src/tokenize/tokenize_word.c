/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize_word.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/30 18:37:03 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/30 19:33:46 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_character(char **new_str, char c, int *j)
{
	(*new_str)[*j] = c;
	(*j)++;
}

static void	toggle_quote(char c, bool *in_quote)
{
	if (c == '"' || c == '\'')
		*in_quote = !*in_quote;
}

static void	handle_backslash(char **new_str, char *str, int *len, int *j)
{
	(*len)++;
	if (str[*len])
		add_character(new_str, str[*len], j);
}

static int	process_word(t_ad_wr *process)
{
	while (process->str[process->len] && \
			!one_of_tokens(process->str[process->len]) && \
			!iswhitespace(process->str[process->len]))
	{
		toggle_quote(process->str[process->len], &process->in_quote);
		if (process->str[process->len] == '\\' && !process->in_quote)
			handle_backslash(&process->new_str, process->str, &process->len, \
							&process->j);
		else
			add_character(&process->new_str, process->str[process->len], \
							&process->j);
		process->len++;
	}
	return (process->len);
}

int	add_word(char *str, int i, t_token **list)
{
	t_ad_wr	*process;

	process = set_process(str, i);
	if (!process)
		return (-1);
	process->len = process_word(process);
	process->new_str[process->j] = '\0';
	if (continue_add_to_word(process->new_str, 0, process->j, list) == -1)
	{
		free(process->new_str);
		free(process);
		return (-1);
	}
	i = process->len;
	free(process->new_str);
	free(process);
	return (i);
}
