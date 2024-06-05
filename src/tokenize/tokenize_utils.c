/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/20 16:40:07 by diwalaku      #+#    #+#                 */
/*   Updated: 2023/11/27 15:59:20 by diwalaku      ########   odam.nl         */
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
int	add_one_token(char *str, int i, char c, t_node **list)
{
	t_node	*new;
	char	*line;

	line = ft_substr(str, i, 1);
	new = create_node(line);
	if (c == '|')
		new->type = PIPE;
	else if (c == '<')
		new->type = REDIR_IN;
	else if (c == '>')
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
