/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_expanding.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/10 18:10:20 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/10 20:41:07 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_pid(char *str, int *i, char **new_str)
{
	int	prev;

	if (*i > 0)
	{
		prev = *i - 1;
		if (str[prev] == '\'')
			printf("hoi");
	}
	printf("klaar\n");
}

bool	is_heredoc_dollar(char *str, int i)
{
	if (str[i] == '$')
	{
		if (str[i + 1] == '{' && is_alph_or_num(str[i + 2]))
			return (true);
		else if (is_alph_or_num(str[i + 1]))
			return (true);
	}
	return (false);
}

t_here_dol	init_heredol(void)
{
	t_here_dol	*new;

	new = mem_check(malloc(sizeof(t_here_dol)));
	new->expanded = NULL;
	new->env_name = NULL;
	new->i = 0;
	new->start_env = 0;
	new->end_var = 0;
	new->brackets = false;
	new->quotes = false;
	new->quote_type = '\0';
	return (new);
}

void	check_quote_and_brackets(char *str, int *i, t_here_dol *var)
{

	if (str[*i - 1] == '\'')
	{
		var->quote_type = '\'';
		var->quotes = true;
	}
	if (str[*i - 1] == '\"')
	{
		var->quote_type = '\"';
		var->quotes = true;
	}
	if (str[*i + 1] == '{')
		var->brackets = true;

}

void	set_heredoc_dollar(char *str, int *i, char **new_string, char **env)
{
	t_here_dol	*info;

	info = init_heredol();
	if (*i > 0)
		check_quote_and_brackets(str, i, info);
	// Check if there's an env-name
	// strdup if there, if not, strdup "".
	if (info->brackets == true)
	{
		// check if there's a closing }. If not: take literal
		// ${USER will be literal.
		printf("here\n");
	}
}

char	*heredoc_expand(char *str, char **env)
{
	char	*new_str;
	int		i;

	i = 0;
	while (str[i])
	{
		if (is_heredoc_dollar(str, i))
			set_heredoc_dollar(str, &i, &new_str, env);
		if (str[i] == '$' && (str[i + 1] == '$'))
			heredoc_pid(str, &i, &new_str);
		else if (str[i] == '$' && (str[i + 1] == '?'))
			heredoc_exit_status(str, &i, &new_str);
	}
	return (new_str);
}
