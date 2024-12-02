# minishell

## Contents

1. [Project Overview](#1-Project-overview)
2. [Project Structure](#2-Project-Structure)
3. [Description of individual steps](#3-Description-of-individual-steps)

## 1. Project overview

For this project, we developed a custom Unix shell, similar in functionality to bash. Our shell can execute commands interactively, manage multiple processes, and supports essential features such as piping, input/output redirection, and environment variable handling. It also includes built-in commands like 'echo', 'cd', and 'pwd', while accurately managing system signals, such as ctrl-C to interrupt processes and ctrl-D to exit the shell.

This project was the first team-based assignment at 42, requiring us to collaborate effectively with Git for version control, strengthening both our technical skills in systems programming and teamwork in software development. For this project I teamed-up with [dhuss42](https://github.com/dhuss42).

## 2. Project structure

Below is the basic structure of the project, with the names in brackets indicating who was responsible for each part:

1. [Environment Variables](#31-Environment-Variables)
2. [Builtins](#32-Builtins)
3. [Lexer](#33-Lexer)
4. [Parser](#34-Parser)
5. [Expansion](#35-Expansion)
6. [Heredoc](#36-Heredoc)
7. [Executor](#37-Executor)
8. [Signals](#38-Signals)

## 3. Description of individual steps

### 3.1 Environment Variables

At program start, environment variables are duplicated and stored in the shell struct, allowing modification throughout the program phases. The SHLVL variable is then incremented by one, so when minishell runs within itself, SHLVL increases by one, just like opening bash within bash.

### 3.2 Builtins

The minishell project implements several core built-in commands to manage the environment and interact with the system. These builtins include `echo`, `env`, `exit`, `export`, `cd`, `pwd`, and `unset`, each handling a specific task in the shell environment.

[cd](https://github.com/maustel/minishell/blob/david_new/builtins/cd.c)
changes the current working directory. If no argument is provided, it changes to the directory specified in the `HOME` variable. It also updates the `PWD` and `OLDPWD` environment variables.

[echo](https://github.com/maustel/minishell/blob/david_new/builtins/echo.c)
outputs the arguments passed to it. It also supports the `-n` flag to prevent printing a newline at the end.

[env](https://github.com/maustel/minishell/blob/david_new/builtins/env.c)
displays the current environment variables that contain an `=` sign, essentially showing the shell's environment.

[exit](https://github.com/maustel/minishell/blob/david_new/builtins/exit.c)
terminates the shell process, optionally accepting an argument to set the exit status. It ensures the exit code is numeric and within the range of 0-255, handling errors and multiple arguments gracefully.

[export](https://github.com/maustel/minishell/blob/david_new/builtins/export.c)
manages the shell's environment variables. It allows new variables to be added or existing ones to be updated. If no arguments are provided, it lists all environment variables in a sorted order.

[pwd](https://github.com/maustel/minishell/blob/david_new/builtins/pwd.c)
prints the current working directory to the output. If the command fails, it displays an error message.

[unset](https://github.com/maustel/minishell/blob/david_new/builtins/unset.c)
removes specified environment variables. It iterates over the environment, creating a new temporary list without the variables to be unset, and then updates the environment with this new list.

### 3.3 Lexer
The lexer serves to transform an input string of characters into meaningful tokens.

It begins by normalizing the input, ensuring that there is a single space between potential tokens, while preserving the integrity of text within single or double quotes. After formatting the string, the lexer splits it into individual components based on spaces, storing these components in a double character array. Each string in the array is then matched with its corresponding token type and stored in a struct, which is added to a linked list for organized access. Finally, the lexer checks the linked list for any syntax errors, ensuring the validity of the parsed input.

### 3.4 Parser
The parser takes the output from the lexer — a linked list of tokens — and organizes them into meaningful structures.

It utilizes a command table to separate these tokens into distinct blocks based on the presence of pipes. Each segment to the left of a pipe is treated as a separate row within the table. The command table itself is implemented as another linked list, featuring a different struct that contains three double character arrays: one for arguments, one for filenames, and one for redirection symbols. To maintain the correct order of the tokens, the parser indexes the associated redirection symbols and filenames using the same variable, ensuring they remain linked appropriately during parsing.

### 3.5 Expansion
The Expansion is responsible for handling the expansion of variables both inside and outside of double quotes while keeping the variables within single quotes in takt. Moreover, it handles the removal of the outer most quote couple.

The function [expansion](expansion/expansion.c) is responsible for coordinating the expansion and the quote removal.

In [check_for_expansion](expansion/check_for_expansion.c) follows an iteration through the table, the args double pointer and the individual strings of args.
While iterating through the individual strings the current character is checked for **"'$ and $?**.
**"** handles the expansion between double quotes
**'** skips the characters between single quotes
**$** handles the ordinary expansion
**$?** extracts the last exit code and expands to it  
Otherwise the iteration through the string continues.

[get_expanded](expansion/get_expanded.c) coordinates the exchange of the variable-to-be-expanded (**$SHLVL**) with the actual expanded string (**1**). First, the variable name is obtained. Then, the variable name is compared in [compare_with_env](expansion/compare_with_env.c) to the list of environment variables. If there is a match the string following the **=** is copied, otherwise and empty string is generated. Next, a temporary string is allocated and populated. It contains the contents of the original string up until the variable name, the expanded variable string and the remainder of the original string. In the final step, the original string in args is freed and replaced with the temporary string.

Example
````
echo "the current Shell level is $SHLVL !!"

[echo][the current Shell level is 1 !!]
````

Lastly, [remove_quotes](expansion/remove_quotes.c) removes the outer most quote couple. It obtains the length of the string without quotes and allocates enough memory for a temporary string. It then populates the string skipping the opening and the closing quote couple. Then the string in args is freed and replaced by the contents of the temporary string.

### 3.6 Heredoc
The heredoc implementation creates separate temporary files for each command with a heredoc encountered (<<'EOF'). A new process handles SIGINT signals separately. Child processes are managed carefully, with proper cleanup and resource management.

Input is obtained using readline, allowing for interactive heredoc creation. Lines are expanded before writing to temporary files (e.g., >hello $USER --> >hello maustel).

When the last heredoc reaches EOF, its content is redirected to stdin, and the temporary file is deleted. This approach efficiently manages heredoc content and cleans up resources after processing.

### 3.7 Executor
The executor uses the linked list, that was prepared in lexer, parser and expander.
It handles single commands, pipes, and redirections. It first checks for existing input (<) and output (> and >>) files, verifying read/write permissions. The last input file for each command is redirected to stdin using dup2, the last output file to stdout/stderr.

For built-in commands, it calls the corresponding function.
Otherwise, it searches for the absolute path, forks a new process, and executes the command using execve().

This implementation allows flexible execution of various command combinations while managing file descriptors and process creation efficiently.

### 3.8 Signals
Signal handling is implemented to manage interrupt and termination signals:

-SIGINT (Ctrl+C): Caught and handled to print a newline followed by a new command line prompt, preventing premature process termination.

-SIGQUIT (Ctrl+\): Ignored, allowing the program to continue running without interruption.

Ctrl+D: Used for graceful shutdown, similar to "exit".


