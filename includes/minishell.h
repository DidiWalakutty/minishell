/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/20 16:38:50 by diwalaku      #+#    #+#                 */
/*   Updated: 2023/12/05 20:27:40 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

// Defining ANSI colors
//

# define SHELL_NAME "Minishell$ " // which name, colors?

typedef enum s_token		t_token;
typedef struct s_expand		t_expand;
typedef struct s_command	t_command;
typedef struct s_node		t_node;
typedef struct s_data		t_data;

// define the tokens we'll need for now.
typedef enum s_token
{
	EMPTY,
	WORD,
	PIPE,			// |  pipe
	REDIR_IN,		// <  in
	REDIR_OUT,		// >  out
	HERE_DOC,		// << heredoc
	APPEND,			// >> append
	DOUBLE_QUOTE,	// "  double qyote = expandable
	SINGLE_QUOTE,	// ' single quote
	DOLLAR,			// $ dollar = do it during expanding
}	t_token;

typedef struct s_expand
{
	int		char_pos;
	int		strlen;
	int		node_i;		// node iterator.
	bool	expandable;
	t_node	*head;
	t_token	prev_type;
	t_token	to_next_node;
}	t_expand;

typedef struct s_dollar
{
	char	*expanded;
	char	*env_name;
	int		i;					// Position in string.
	int		str_len;			// Length of full node->str.
	int		start_env;			// Position after $ and/or ${.
	int		end_var;			// Position where env-name ends.
	int		env_length;			// Length of found env.
	bool	brackets;			// In case of ${}
	bool	remainder;			// Check for if we need to re-read the node
}	t_dollar;

typedef struct s_command
{	

}	t_command;

// word: 	a pointer to the string stored in a node
// len: 	the content length
// type: 	the content token
typedef struct s_node
{
	char			*str;
	t_token			type;
	t_node			*next;
	t_node			*previous;
	// state?
	// set i?
}	t_node;

typedef struct s_data
{
	// int		i; add for iterating with data->i in tokenize_input?
	char	*input;
	char	**env;
	t_node	*list;
	t_command *commands;
	// t_token	*token;	// needed in t_node??
	size_t	process;
}	t_data;

// Functions //
// Environment and paths;
char	**copy_env(char **env);

// Lexer
int		lexer_and_parser(t_data *data);
bool	all_quotes_closed(char *str);
bool	skip_quotedstring(char *str, int *i);
t_node	*tokenize_input(t_data *data, char *str);

// Tokenize and Expanding
int		add_quote(char *str, int i, char c, t_node **list);
int		add_redir_or_pipe(char *str, int i, t_data *data, t_node **list);
int		add_one_token(char *str, int i, t_data *data, t_node **list);
int		add_dollar(char *str, int i, t_node **list);
int		add_word(char *str, int i, t_node **list);
void	expand_input(t_node *list, char **env);
// t_node	*expander(t_node *list, char **env);

// Utils
bool	one_of_tokens(char c);
void	skip_to_token(char *str, int *i);
void	skip_whitespace(char *str, int *i);
int		quote_length(char *str, char c);
int		variable_len(char *str);

// Utils - Expanding
char	*copy_env_input(char **env, char *to_find);
int		if_valid_char(char c);
bool	is_double_dollar(t_node *node, t_expand *info, bool is_expandable);
void	set_pid(t_node *node, t_expand *info);
bool	is_dollar(t_node *node, bool is_expandable);
int		set_dollar(t_node *node, char **env, t_expand *info);
// t_node	*expand_node(t_node *node, t_dollar *var);
t_node	*expand_node(t_node *node, t_dollar *var, t_expand *info);

// Nodes
t_node	*create_node(char *str, t_token type);
void	node_to_list(t_node **list, t_node *new);

// Free and exit
// exit_error(char *str); probably not needed
void	free_array(char **str);
bool	error_msg(char *message, char c);
void	free_all(t_data	*data);
int		free_dollarvar(t_dollar *var);

// List_utils
t_node	*attach_list_token(t_node **head, t_node *new_node);

// For Testing
const char	*type_to_string(t_token type);
void		print_linked_list(t_node *head);
void		print_env(char **env);

#endif
