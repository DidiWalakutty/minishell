/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                       :+:    :+:             */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/20 16:38:50 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/07/26 16:33:33 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
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
}  t_token;

// word: 	a pointer to the string stored in a node
// len: 	the content length
// type: 	the content token

typedef struct s_cmd
{
	pid_t	pid;
	char	*cmd;
	char	*path;
	char	**args;
	char	*redirect_in;
	char	*redirect_out;
	char	**env;
	t_cmd	*next;
} t_cmd;

typedef struct s_node
{
	char			*str;
	t_token			type;
	t_node			*next;
	t_node			*previous;
	// state?
	// set i?
}  t_node;

typedef struct s_data
{
	char	*input;
	char	**env;
	t_node	*list;
	t_token	*token;
	t_cmd	*cmd_process;
	size_t	process;
}	t_data;


// Functions //

// Environment and paths;
char	**copy_env(char **env);

// Lexer
int		lexer(t_data *data);
bool	all_quotes_closed(char *str);
bool	skip_quotedstring(char *str, int *i);
t_node	*tokenize_input(t_data *data, char *str);

// Tokenize
int	add_quote(char *str, int i, char c, t_node **list);
int	add_redir(char *str, int i, char c, t_node **list);
int	add_one_token(char *str, int i, char c, t_node **list);
int	add_dollar(char *str, int i, t_node **list);
int	add_space(char *str, int i, t_node **list);

// Utils
bool	one_of_tokens(char c);
void 	skip_to_token(char *str, int *i);
void	skip_whitespace(char *str, int *i);
int		quote_length(char *str, char c);
int		add_one_token(char *str, int i, char c, t_node **list);
int		variable_len(char *str);

// still needed?
int		add_word(char *str, int i, t_node **list);
int		add_tokens(char *str, int i, t_node **list);

// Nodes
t_node	*create_node(char *str);
void	node_to_list(t_node **list, t_node *new);

// Free and exit
void		free_array(char **str);
bool		error_msg(char *message, char c);
const char 	*type_to_string(t_token type);

// Executing
void	error_exit(const char *msg, int status);
int		make_processes(t_data *data);

// Builtins
void	echo_builtin(const char *str, bool newline);
void	cd_builtin(const char *dst_directory);
void	pwd_builtin(void);

#endif
