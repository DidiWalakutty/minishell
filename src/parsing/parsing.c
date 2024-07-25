/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parsing.c                                         :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/07/25 19:51:53 by sreerink      #+#    #+#                 */
/*   Updated: 2024/07/25 19:52:33 by sreerink      ########   odam.nl         */
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

void	write_cmd_words(t_cmd **cmd, t_node **list)
{
	size_t	i;

	i = 0;
	(*cmd)->cmd = ft_strdup((*list)->str);
	if (!(*cmd)->cmd)
		error_exit("ft_strdup", EXIT_FAILURE);
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
	if ((list && (*list)->type == 3) || pipe_in)
		write_redirect_in(cmd, list);
	if (list && ((*list)->type == 2 || (*list)->type == 4 || (*list)->type == 6))
	{
		write_redirect_out(cmd, list);
		if ((*list)->type == 2)
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
	cmds_n = data->pipe_num - 1;
	head = ft_calloc(1, sizeof(t_cmd));
	if (!head)
		error_exit("ft_calloc", EXIT_FAILURE);
	last = head;
	write_cmd_data(&head, &cur_list);
	while (cmds_n)
	{
		new = ft_calloc(1, sizeof(t_cmd));
		if (!new)
			error_exit("ft_calloc", EXIT_FAILURE);
		last->next = new;
		last = new;
		write_cmd_words(&last, &cur_list);
		cmds_n--;
	}
	last->next = NULL;
	return (head);
}
