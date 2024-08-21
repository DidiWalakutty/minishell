// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   build_utils.c                                      :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2024/08/21 13:44:10 by diwalaku      #+#    #+#                 */
// /*   Updated: 2024/08/21 13:45:25 by diwalaku      ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// bool	a_redirection(t_node *node)
// {
// 	if (node->type == REDIR_IN || node->type == REDIR_OUT || \
// 		node->type == APPEND || node->type == HERE_DOC)
// 		return (true);
// 	return (false);
// }

// // Checks for space-input only and
// // pipe_usage.
// int	not_just_spaces(t_node *nodes)
// {
// 	int		count;
// 	bool	flag;

// 	count = 0;
// 	flag = false;
// 	while (nodes)
// 	{
// 		if (nodes->type == SEPARATOR)
// 			flag = true;
// 		count++;
// 		nodes = nodes->next;
// 	}
// 	if (flag && count == 1)
// 		return (0);
// 	return (1);
// }
