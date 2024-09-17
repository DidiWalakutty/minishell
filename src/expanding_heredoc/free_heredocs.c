/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_heredocs.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/17 21:01:44 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/17 21:11:21 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

static void	free_redir_in(t_redin *redir_in)
{
	t_redin	*temp;

	while (redir_in)
	{
		temp = redir_in;
		redir_in = redir_in->next;
		if (temp->str)
			free(temp->str);
		free(temp);
	}
}

static void	free_redir_out(t_redou *redir_out)
{
	t_redou	*temp;

	while (redir_out)
	{
		temp = redir_out;
		redir_out = redir_out->next;
		if (temp->str)
			free(temp->str);
		free(temp);
	}
}

void	free_cmds(t_cmd *cmd_list)
{
	t_cmd	*temp;

	while (cmd_list)
	{
		temp = cmd_list;
		cmd_list = cmd_list->next;
		if (temp->cmd)
			free(temp->cmd);
		if (temp->path)
			free(temp->path);
		if (temp->args)
			free_args(temp->args);
		if (temp->redir_in)
			free_redir_in(temp->redir_in);
		if (temp->redir_out)
			free_redir_out(temp->redir_out);
		free(temp);
	}
}
