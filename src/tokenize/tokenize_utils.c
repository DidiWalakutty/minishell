/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 15:38:34 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/07/26 13:16:44 by diwalaku      ########   odam.nl         */
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

int	variable_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' || iswhitespace(str[i]) || \
			str[i] == '\'' || str[i] == '\"' || \
			str[i] == '<' || str[i] == '>' || str[i] == '|')
			break ;
		i++;
	}
	return (i);
}
