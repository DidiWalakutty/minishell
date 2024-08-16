/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 15:38:34 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/08/16 19:47:36 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	one_of_tokens(char c)
{
	if (c == '\'' || c == '\"' || c == '<' || c == '>' || \
		c == '|')
		return (true);
	return (false);
}

void	skip_to_token(char *str, int *i)
{
	while (str[*i] != '\0' && str[*i] != '\'' && str[*i] != '\"' && \
			str[*i] != '|' && str[*i] != '>' && str[*i] != '<')
		(*i)++;
}

void	skip_whitespace(char *str, int *i)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
}

// Add one token to the list: either |, < or >.
// Return i + 1, so we get the i immediately after the token.
int	add_one_token(char *str, int i, t_data *data, t_node **list)
{
	t_node	*new;
	char	*line;

	line = ft_substr(str, i, 1);
	new = create_node(line, EMPTY);
	if (str[i] == '|')
	{
		new->type = PIPE;
		data->process += 1;
	}
	else if (str[i] == '<')
		new->type = REDIR_IN;
	else if (str[i] == '>')
		new->type = REDIR_OUT;
	node_to_list(list, new);
	return (i + 1);
}

bool	check_start_pipes(char *str, int *i)
{
	if (str[*i + 1] == '|')
		return (error_msg("syntax error near unexpected token", \
				str[*i], str[*i + 1]));
	else
		return (error_msg("syntax error near unexpected token", \
				str[*i], '\0'));
}
