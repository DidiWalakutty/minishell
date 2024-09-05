/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build_inits_and_nodes.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/23 15:45:42 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/05 17:52:29 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_redirects(t_cmd *cmd)
{
	cmd->redir_in = NULL;
	cmd->redir_out = NULL;
}

t_cmd	*init_cmds(void)
{
	t_cmd	*command;

	command = malloc(sizeof(t_cmd));
	command->command = NULL;
	command->args = NULL;
	command->type = EMPTY;
	command->redir_in = NULL;
	command->redir_out = NULL;
	command->next = NULL;
	return (command);
}

t_redir_in	*dup_redir_in_node(t_redir_in *redir)
{
	t_redir_in	*new_node;

	new_node = malloc(sizeof(t_redir_in));
	if (!new_node)
		return (NULL);
	new_node->str = ft_strdup(redir->str);
	if (!new_node->str)
		return (NULL);
	new_node->heredoc = redir->heredoc;
	new_node->quotes = redir->quotes;
	new_node->next = NULL;
	return (new_node);
}

t_redir_out	*dup_redir_out_node(t_redir_out *redir)
{
	t_redir_out	*new_node;

	new_node = malloc(sizeof(t_redir_out));
	if (!new_node)
		return (NULL);
	new_node->str = ft_strdup(redir->str);
	if (!new_node->str)
		return (NULL);
	new_node->append = redir->append;
	new_node->next = NULL;
	return (new_node);
}

void	free_curr_cmd(t_cmd *command)
{
	int	i;

	i = 0;
	if (command->command)
		free(command->command);
	if (command->args)
	{
		while (command->args[i])
		{
			free(command->args[i]);
			i++;
		}
		free(command->args);
	}
	free(command);
}
