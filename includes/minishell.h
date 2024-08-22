/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                       :+:    :+:             */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/20 16:38:50 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/08/03 23:56:21 by sreerink      ########   odam.nl         */
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

typedef enum s_token		t_type;
typedef struct s_list		t_list;
typedef struct s_cmd		t_cmd;
typedef struct s_expand		t_expand;
typedef struct s_redir_var	t_redir_var;
typedef struct s_node		t_token;
typedef struct s_data		t_data;

// define the tokens we'll need for now.
typedef enum s_token
{
	EMPTY,
	SEPARATOR,		// spaces, ' ' used for parsing only.
	WORD,			// Word
	PIPE,			// |  pipe
	REDIR_IN,		// <  in
	REDIR_OUT,		// >  out
	HERE_DOC,		// << heredoc
	APPEND,			// >> append
	DOUBLE_QUOTE,	// "  double qyote = expandable
	SINGLE_QUOTE,	// '  single quote
	DOLLAR,			// $ dollar = do it during expanding
}	t_type;

typedef struct s_expand
{
	int		char_pos;
	int		strlen;
	int		node_i;		// node iterator.
	int		heredoc_pos;
	bool	expandable;
	t_token	*head;
	t_type	prev_type;
}	t_expand;

typedef struct s_dollar
{
	char	*expanded;
	char	*env_name;
	int		i;					// Position in string.
	int		str_len;			// Length of full node->str.
	int		start_env;			// Position after $ and/or ${.
	int		end_var;			// Position where env-name ends.
	bool	brackets;			// In case of ${}
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
}	t_builtin;

// typedef struct s_cmd
// {
// 	pid_t	pid;
// 	char		*cmd;
// 	char		*path;
// 	char		**args;
// 	char		*redirect_in;
// 	char		*&redirect, redirect_out;
// 	char		**env;
// 	bool		append;
// 	t_builtin	builtin;
// 	t_cmd		*next;
// } t_cmd;

typedef struct s_cmd_var
{
	char	*command;
	char	**arguments;
}	t_cmd_var;

typedef struct s_redir_in
{
	char	*str;
	bool	heredoc;
	// bool	quotes;
	t_redir_in *next;
}	t_redir_in;

typedef struct s_redir_out
{
	char		*str;
	bool		append;
	t_redir_out	*next;
}	t_redir_out;

typedef struct s_cmd
{
	char		*command;
	char		**args;
	t_type		type;
	t_redir_in	*redir_in;
	t_redir_out	*redir_out;
	t_cmd		*next;
}	t_cmd;

typedef struct s_node
{
	char	*str;
	t_type	type;
	t_token	*next;
	bool	null;	
}	t_token;

typedef struct s_data
{
	char	*input;
	char	**env;
	t_token	*list;
	t_type	*token;
	t_cmd	*cmd_process;
	size_t	process;
	int		exit_status;
	char	*home;
	int		shlvl;
}	t_data;

// Functions //
// Environment and paths;
char	**copy_env(char **env);

// Lexer
int		tokenizer_and_parser(t_data *data);
bool	all_quotes_closed(char *str);
bool	skip_quotedstring(char *str, int *i);
t_token	*tokenize_input(t_data *data, char *str);

// Tokenize
int		add_quote(char *str, int i, char c, t_token **list);
int		add_redir_or_pipe(char *str, int i, t_data *data, t_token **list);
int		add_one_token(char *str, int i, t_data *data, t_token **list);
int		add_dollar(char *str, int i, t_token **list);
int		add_word(char *str, int i, t_token **list);
void	expand_input(t_data *data, t_token *node, char **env);

// Utils - Tokenizer
bool	one_of_tokens(char c);
void	skip_to_token(char *str, int *i);
void	skip_whitespace(char *str, int *i);
int		quote_length(char *str, char c);
bool	check_start(char *str, int *i);

// Expanding
bool	check_null(t_token **node);
bool	is_exit_status(t_token *node);
int		set_exit_status(t_data *data, t_token *node, t_expand *info);
bool	is_double_dollar(t_token *node);
int		set_pid(t_token *node, t_expand *info);
bool	is_dollar(t_token *node);
int		set_dollar(t_token *node, char **env, t_expand *info);
bool	quote_type_present(t_token *node);
int		concatenate_quotes(t_token *node);

// Utils - Expanding
char	*copy_env_input(char **env, char *to_find);
int		if_valid_char(char c);
void	expand_node(t_token *node, t_dollar *var);
bool	quote_type_present(t_token *node);
int		concatenate_quotes(t_token *list);
bool	spaces_present(t_token *node);
int		remove_spaces(t_token *list);

// Nodes
t_token	*create_node(char *str, t_type type);
void	node_to_list(t_token **list, t_token *new);

// Commands (Didi's Part)
t_cmd	*build_commands(t_token *nodes, t_data *data);

// Commands - Utils (Didi's Part)
bool	a_redirection(t_token *node);
int		not_just_spaces(t_token *nodes);

// Free and exit
// exit_error(char *str); probably not needed
void	free_array(char **str);
bool	error_msg(char *message, char c, char c2);
void	free_all(t_data	*data);
void	free_node(t_token *node);

// List_utils
t_token	*last_token(t_token *list);

// For Testing
const char	*type_to_string(t_type type);
void	print_linked_list(t_token *head);
void	print_env(char **env);

// Parsing
t_cmd	*make_cmd_nodes(t_data *data);

// Executing
void	error_exit(const char *msg, int status);
int		make_processes(t_data *data);

// Builtins
void	echo_builtin(const char *str, bool newline);
void	cd_builtin(const char *dst_directory);
void	pwd_builtin(void);

#endif
