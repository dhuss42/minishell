# minishell

## Contents

1. [Project Overview](#1-Project-overview)
2. [Project Structure](#2-Project-Structure)
3. [Description of individual steps](#3-Description-of-individual-steps)

## 1. Project overview

For this project, we developed a custom Unix shell, similar in functionality to bash. Our shell can execute commands interactively, manage multiple processes, and supports essential features such as piping, input/output redirection, and environment variable handling. It also includes built-in commands like 'echo', 'cd', and 'pwd', while accurately managing system signals, such as ctrl-C to interrupt processes and ctrl-D to exit the shell.

This project was the first team-based assignment at 42, requiring us to collaborate effectively with Git for version control, strengthening both our technical skills in systems programming and teamwork in software development. For this project I teamed-up with [maustel](https://github.com/maustel).

## 2. Project structure

Below is the basic structure of the project, with the names in brackets indicating who was responsible for each part:

1. 
2. Lexer (dhuss)
3. Parser (dhuss)
4. Expansion (dhuss)
5. Executer (maustel)

## 3. Description of individual steps

### Lexer

The lexer serves to transform an input string of characters into meaningful tokens. 

It begins by normalizing the input, ensuring that there is a single space between potential tokens, while preserving the integrity of text within single or double quotes. After formatting the string, the lexer splits it into individual components based on spaces, storing these components in a double character array. Each string in the array is then matched with its corresponding token type and stored in a struct, which is added to a linked list for organized access. Finally, the lexer checks the linked list for any syntax errors, ensuring the validity of the parsed input.

### Parser

The parser takes the output from the lexer—a linked list of tokens—and organizes them into meaningful structures. 

It utilizes a command table to separate these tokens into distinct blocks based on the presence of pipes. Each segment to the left of a pipe is treated as a separate row within the table. The command table itself is implemented as another linked list, featuring a different struct that contains three double character arrays: one for arguments, one for filenames, and one for redirection symbols. To maintain the correct order of the tokens, the parser indexes the associated redirection symbols and filenames using the same variable, ensuring they remain linked appropriately during parsing.

### Expansion

### Executer
