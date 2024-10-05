# Minishell

Welcome to our Minishell!
This collaborative group project was created with [Sam Reerink](https://github.com/samreerink).

## About Minishell
With this project, we built a basic shell (similar to bash) that handles command execution, <br>environment variable management, signal handling, and input redirection. 
<br><br>
The goal is to create a fully functional command-line interpreter that allows users to execute commands, 
expand env-variables, manage processes and handle input/output redirection. <br><br>
Through this project, we have gained a deeper understanding of process management, file descriptors, and 
how shells interact with the operating system.

## Builtins 🔧

| Builtin       | Description    |
| ------------- |-------------|
| echo          | Prints text, a string or an env-variable to the standard output. <br> With the -n flag: prevents adding a newline at the end. |
| cd            | Changes the current working directory to the specified path.|
| pwd           | Displays the absolute path of the current working directory.   |
| export        | Lists all the exported environment variables in the shell. |
| unset         | Removes a variable or function from the shell environment. |
| env           | Displays the environment variables for the current shell session.|
| exit          | Exits the shell, terminating the session. |

## Key learning areas 🎯

• Handling multiple processes.<br>
• Managing file descriptors.<br>
• Tokenization.<br>
• Expanding environment variables.<br>
• Implementing shell features (pipes, redirections).


## Installation :desktop_computer:

To try our Minishell yourself, please follow the next steps:

1.  Compile the game with the following command:
```
$ make
```
2. Execute it with the following command:
```
> $ ./minishell
````
