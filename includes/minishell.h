/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                       :+:    :+:             */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/20 16:38:50 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/08/24 23:11:31 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <linux/limits.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>

// Defining ANSI colors
//

# define SHELL_NAME "Minishell$ " // which name, colors?

typedef enum s_token		t_token;
typedef struct s_list		t_list;
typedef struct s_cmd		t_cmd;
typedef struct s_expand		t_expand;
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

// word: 	a pointer to the string stored in a node
// len: 	the content length
// type: 	the content token
typedef enum s_builtin
{
	NO_BUILTIN,
	CD,
	EXPORT,
	UNSET,
	EXIT,
	ECHO,
	PWD,
	ENV,
} t_builtin;

typedef struct s_cmd
{
	pid_t	pid;
	char		*cmd;
	char		*path;
	char		**args;
	char		*redirect_in;
	char		*redirect_out;
	char		**env;
	bool		append;
	t_builtin	builtin;
	t_cmd		*next;
} t_cmd;

typedef struct s_node
{
	char	*str;
	t_token	type;
	t_node	*next;
	t_node	*previous;
	bool	null;	
	// state?
	// set i?
}	t_node;

typedef struct s_data
{
	// int		i; add for iterating with data->i in tokenize_input?
	char	*input;
	char	**env;
	t_node	*list;
	t_token	*token;
	t_cmd	*cmd_process;
	// t_token	*token;	// needed in t_node??
	size_t	process;
	int		exit_status;
}	t_data;

// Functions //
// Environment and paths;
char	**copy_env(char **env);
char	**make_env_var(char *new_var, char *value, char **env);
bool	replace_var_value(char *new_value, char *var_dst, char **env);

// Lexer
int		lexer_and_parser(t_data *data);
bool	all_quotes_closed(char *str);
bool	skip_quotedstring(char *str, int *i);
t_node	*tokenize_input(t_data *data, char *str);

// Tokenize
int		add_quote(char *str, int i, char c, t_node **list);
int		add_redir_or_pipe(char *str, int i, t_data *data, t_node **list);
int		add_one_token(char *str, int i, t_data *data, t_node **list);
int		add_dollar(char *str, int i, t_node **list);
int		add_word(char *str, int i, t_node **list);
void	expand_input(t_data *data, t_node *node, char **env);

// Utils - Tokenizer
bool	one_of_tokens(char c);
void	skip_to_token(char *str, int *i);
void	skip_whitespace(char *str, int *i);
int		quote_length(char *str, char c);
int		variable_len(char *str);

// Expanding
bool	check_null(t_node **node);
bool	is_exit_status(t_node *node, bool expandable);
int		set_exit_status(t_data *data, t_node *node, t_expand *info);
bool	is_double_dollar(t_node *node, bool is_expandable);
int		set_pid(t_node *node, t_expand *info);
bool	is_dollar(t_node *node, bool is_expandable);
int		set_dollar(t_node *node, char **env, t_expand *info);

// Utils - Expanding
char	*copy_env_input(char **env, char *to_find);
int		if_valid_char(char c);
void	expand_node(t_node *node, t_dollar *var);

// Utils (general)
bool	str_is_all_digits(char *str);

// Nodes
t_node	*create_node(char *str, t_token type);
void	node_to_list(t_node **list, t_node *new);
void	attach_new_node(t_node *head, t_node *og, int node_i, bool empty_node);

// Free and exit
// exit_error(char *str); probably not needed
void	free_env_array(char **str);
bool	error_msg(char *message, char c);
void	free_all(t_data	*data);
int		free_dollarvar(t_dollar *var);

// List_utils
t_node	*last_node(t_node *list);
t_node	*attach_list_token(t_node **head, t_node *new_node);

// For Testing
const char	*type_to_string(t_token type);
void		print_linked_list(t_node *head);
void		print_env(char **env);

// Parsing
t_cmd	*make_cmd_nodes(t_data *data);

// Executing
void	error_exit(const char *msg, int status);
int		make_processes(t_data *data);

// Builtins
int		execute_builtin(t_cmd *cmd, t_data *data);
int		cd_builtin(t_cmd *cmd, t_data *data);
int		echo_builtin(t_cmd *cmd);
int		pwd_builtin(void);
int		exit_builtin(t_cmd *cmd, t_data *data);

#endif
