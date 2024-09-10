/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   testing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/06 14:11:29 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/10 15:18:07 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_redin(t_redin *redir)
{
	int i = 0;
	while (redir)
	{
		printf("- %i - String: %s\n", i, redir->str);
		printf("      Heredoc: %d - Quotes: %d\n", redir->heredoc, redir->quotes);
		redir = redir->next;
	}
}

void	print_redou(t_redou *redir)
{
	int i = 0;
	while (redir)
	{
		printf("- %i - String: %s\n", i, redir->str);
		printf("      Append: %d\n\n", redir->append);
		redir = redir->next;
	}
}

void	print_commands(t_cmd *cmd)
{
	int i = 1;
	while (cmd)
	{
		printf("\n--- Command node %i ---\n", i);
		printf("command: %s\n", cmd->command);
		printf("arguments:\n");
		if (cmd->args)
		{
			for (int i = 0; cmd->args[i] != NULL; i++)
				printf("- %i - %s\n", i, cmd->args[i]);
		}
		printf("____________________\n");
		printf("- Redirect In: -\n");
		print_redin(cmd->redir_in);
		printf("\n");
		printf("____________________\n");
		printf("- Redirect Out: -\n");
		print_redou(cmd->redir_out);
		printf("\n---Next Command---\n\n");
		cmd = cmd->next;
	}
}

// to printf check type
const char	*type_to_string(t_type type)
{
	switch(type)
	{
		case EMPTY: return "EMPTY";
		case SEPARATOR: return "SPACE";
		case WORD: return "WORD";
		case PIPE: return "PIPE";
		case REDIR_IN: return "REDIR_IN";
		case REDIR_OUT: return "REDIR_OUT";
		case HERE_DOC: return "HERE_DOC";
		case APPEND: return "APPEND";
		case DOUBLE_QUOTE: return "DOUBLE_QUOTE";
		case SINGLE_QUOTE: return "SINGLE_QUOTE";
		default: return "UNKNOWN";
	}
}

void	print_linked_list(t_token *head)
{
	int i = 1;
	while (head != NULL)
	{
		printf("Node %i is: %s - type is: %s \n", i, head->str, type_to_string(head->type));
		head = head->next;
		i++;
	}
	printf("\n");
}

void	print_env(char **env)
{
	int	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}


