/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_expanding.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/10 18:10:20 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/11 19:15:04 by didi          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_heredoc_dollar(char *str, int *i, char **new_string, char **env)
{
	t_h_dol	*info;
	char	*temp;

	info = init_heredol();
	if (*i > 0)
		check_quote_and_brackets(str, i, info);
	set_env_and_expand(str, i, info, env);
	temp = *new_string;
	new_string = ft_strjoin(*new_string, info->expanded);
	free(temp);
	free_heredoc_info(info);
}

void	set_heredoc_pid(char *str, int *i, char **new_string, char **env)
{
	t_h_dol	*info;
	char	*pid;
	char	*temp;

	pid = ft_itoa(getpid());
	info = init_heredol();
	if (*i > 0)
		check_quote_and_brackets(str, i, info);
	expand_heredoc_pid(str, i, info, env);
	temp = *new_string;
	new_string = ft_strjoin(*new_string, info->expanded);
	free(temp);
	free_heredoc_info(info);

}

char	*heredoc_expanding(char *str, char **env)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = ft_strdup("");
	while (str[i])
	{
		if (is_heredoc_dollar(str, i))
			set_heredoc_dollar(str, &i, &new_str, env);
		else if (is_heredoc_pid(str, i))
			set_heredoc_pid(str, &i, &new_str, env);
		else if (is_heredoc_exit(str, i))
			heredoc_exit_status(str, &i, &new_str, env);
		else
			new_str = add_to_heredoc_string(new_str, str[i]);
		i++;
	}
	return (new_str);
}
