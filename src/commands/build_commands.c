// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   build_commands.c                                   :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2024/08/12 17:57:27 by diwalaku      #+#    #+#                 */
// /*   Updated: 2024/08/21 15:16:07 by diwalaku      ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// t_redir	*set_redirect(void)
// {
// 	t_redir	*redirect;

// 	redirect = malloc(sizeof(t_redir));

// }

// t_cmd	*merge_commands(t_node *node, t_data *data)
// {
// 	t_cmd		*commands;

// 	while (node)
// 	{
// 		if (a_redirection(node->type) == true)
// 		{
// 			if (handle_redirect(&node, &redirect, data) == 1)
// 				printf("check for failure and free");
// 		}
// 	}
// 	return (commands);
// }

// t_cmd	*build_commands(t_node *nodes, t_data *data)
// {
// 	t_cmd		*commands;

// 	commands = NULL;
// 	if (nodes && not_just_spaces(nodes))
// 	{
// 		commands = merge_commands(nodes, data);
// 		if (!commands)
// 			printf("free things");
// 		// handle_them
// 	}
// 	return (commands);
// }
