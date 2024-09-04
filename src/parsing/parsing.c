/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parsing.c                                         :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/07/25 19:51:53 by sreerink      #+#    #+#                 */
/*   Updated: 2024/09/03 19:19:17 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	count_args(t_node *list)
{
	size_t	n;

	n = 0;
	while (list && list->type == WORD)
	{
		n++;
		list = list->next;
	}
	return (n);
}

void	check_cmd_builtin(t_cmd **cmd)
{
	if (!strncmp("cd", (*cmd)->cmd, 3))
		(*cmd)->builtin = CD;
	else if (!strncmp("export", (*cmd)->cmd, 7))
		(*cmd)->builtin = EXPORT;
	else if (!strncmp("unset", (*cmd)->cmd, 6))
		(*cmd)->builtin = UNSET;
	else if (!strncmp("exit", (*cmd)->cmd, 5))
		(*cmd)->builtin = EXIT;
	else if (!strncmp("echo", (*cmd)->cmd, 5))
		(*cmd)->builtin = ECHO;
	else if (!strncmp("pwd", (*cmd)->cmd, 4))
		(*cmd)->builtin = PWD;
	else if (!strncmp("env", (*cmd)->cmd, 4))
		(*cmd)->builtin = ENV;
}

void	write_cmd_words(t_cmd **cmd, t_node **list)
{
	size_t	i;

	i = 0;
	(*cmd)->cmd = ft_strdup((*list)->str);
	if (!(*cmd)->cmd)
		error_exit("ft_strdup", EXIT_FAILURE);
	check_cmd_builtin(cmd);
	while (*list && (*list)->type == WORD)
	{
		(*cmd)->args[i] = ft_strdup((*list)->str);
		if (!(*cmd)->args)
			error_exit("ft_strdup", EXIT_FAILURE);
		i++;
		*list = (*list)->next;
	}
}

void	write_redirect_in(t_cmd **cmd, t_node **list)
{
	if (*list && (*list)->type == REDIR_IN)
	{
		(*cmd)->redirect_in = ft_strdup((*list)->next->str);
		if (!(*cmd)->redirect_in)
			error_exit("ft_strdup", EXIT_FAILURE);
		*list = (*list)->next->next;
	}
	else if (*list && (*list)->type == HERE_DOC)
	{
		(*cmd)->redirect_in = ft_strdup((*list)->next->str);
		if (!(*cmd)->redirect_in)
			error_exit("ft_strdup", EXIT_FAILURE);
		(*cmd)->heredoc = true;
		*list = (*list)->next->next;
	}
	else
	{
		(*cmd)->redirect_in = ft_strdup("|");
		if (!(*cmd)->redirect_in)
			error_exit("ft_strdup", EXIT_FAILURE);
	}
}

void	write_redirect_out(t_cmd **cmd, t_node **list)
{
	if ((*list)->type == REDIR_OUT)
	{
		(*cmd)->redirect_out = ft_strdup((*list)->next->str);
		if (!(*cmd)->redirect_out)
			error_exit("ft_strdup", EXIT_FAILURE);
	}
	else if ((*list)->type == APPEND)
	{
		(*cmd)->append = true;
		(*cmd)->redirect_out = ft_strdup((*list)->next->str);
		if (!(*cmd)->redirect_out)
			error_exit("ft_strdup", EXIT_FAILURE);
	}
	else if ((*list)->type == PIPE)
	{
		(*cmd)->redirect_out = ft_strdup("|");
		if (!(*cmd)->redirect_out)
			error_exit("ft_strdup", EXIT_FAILURE);
		return ;
	}
	*list = (*list)->next->next;
}

void	write_cmd_data(t_cmd **cmd, t_node **list)
{
	size_t	args_len;
	bool	pipe_in;

	pipe_in = false;
	if ((*list)->type == PIPE)
	{
		pipe_in = true;
		*list = (*list)->next;
	}
	args_len = count_args(*list);
	(*cmd)->args = malloc(sizeof(char *) * (args_len + 1));
	if (!(*cmd)->args)
		error_exit("malloc", EXIT_FAILURE);
	(*cmd)->args[args_len] = NULL;
	write_cmd_words(cmd, list);
	if (pipe_in || (*list && (*list)->type == REDIR_IN) || (*list && (*list)->type == HERE_DOC))
		write_redirect_in(cmd, list);
	if (*list && ((*list)->type == PIPE || (*list)->type == REDIR_OUT || (*list)->type == APPEND))
	{
		write_redirect_out(cmd, list);
		if (*list && (*list)->type == PIPE)
			return ;
	}
}

t_cmd	*make_cmd_nodes(t_data *data)
{
	t_cmd	*head;
	t_cmd	*new;
	t_cmd	*last;
	t_node	*cur_list;
	size_t	cmds_n;

	cur_list = data->list;
	cmds_n = data->process - 1;
	head = ft_calloc(1, sizeof(t_cmd));
	if (!head)
		error_exit("ft_calloc", EXIT_FAILURE);
	last = head;
	last->env = data->env;
	write_cmd_data(&head, &cur_list);
	while (cmds_n)
	{
		new = ft_calloc(1, sizeof(t_cmd));
		if (!new)
			error_exit("ft_calloc", EXIT_FAILURE);
		last->next = new;
		last = new;
		last->env = data->env;
		write_cmd_data(&last, &cur_list);
		cmds_n--;
	}
	last->next = NULL;
	return (head);
}
