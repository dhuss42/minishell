/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:59:19 by maustel           #+#    #+#             */
/*   Updated: 2024/11/27 17:10:03 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

# ifndef BASE_PATH
#  define BASE_PATH "executor/tmp/heredoc_temp"
# endif

//----------------structs--------------//

typedef enum e_token_type
{
	TOKEN_PIPE,
	TOKEN_REDIN,
	TOKEN_REDOUT,
	TOKEN_HEREDOC,
	TOKEN_REDAPPEND,
	TOKEN_SQUOTES,
	TOKEN_DQUOTES,
	TOKEN_ARGS,
	TOKEN_EXITSTATUS,
	TOKEN_WORD,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*input;
}	t_token;

typedef struct s_command
{
	char	**args;
	char	**filename;
	char	**red_symbol;
	int		id;
	char	*path;				//to free
	char	*final_infile;
	char	*final_outfile;
	char	*final_in_red;
	char	*final_out_red;
	int		original_stdout;
	int		original_stdin;
	char	*heredoc_file_path;	//to free
}	t_command;

typedef struct s_shell
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	len;
	size_t	lines;
	size_t	words;
	size_t	reds;
	size_t	filenames;
	t_list	*tmp;
	t_list	*list;
	t_list	*table;
	bool	isspace;
	bool	syntax_error;
	bool	exit;
	bool	rem;
	char	quote;
	char	*res;
	char	**env;
	pid_t	*pid;	//free required
	int		**fd;	//double free required
}	t_shell;

typedef enum e_custom_err
{
	E_PATH = 107,
	E_FILENOEXIST,
	E_DIRNOEXIST,
	E_NOPERMISSION_PATH,
	E_NOPERMISSION_FILE,
	E_INIT_TERMINAL,
	E_ISDIRECTORY,
	E_BUILTIN,
	E_FILE_ISDIRECTORY,
	E_TOOMANYARG,
	E_NOTVALIDIDENT,
	E_CDNOSUCHFOD,
	E_NOTSET,
	E_NUMERICARG = 255,
	E_SYNTAXERROR = 258
}			t_custom_err;

typedef enum e_print_err
{
	NOTPRINT,
	PRINT
}			t_print_err;

//t_list:
//void *content --> t_command *example
//t_list *next

// typedef struct s_command
// {
// 	char	**args;
// 	char	**filename;
// 	char	**red_symbol;
// 	int		id;
// 	char	*path;				//to free
// 	char	*final_infile;
// 	char	*final_outfile;
// 	char	*final_in_red;
// 	char	*final_out_red;
// 	char	*heredoc_file_path;	//to free
// } t_command;

// typedef struct	s_exec
// {
// 	// int		exit_code;
// 	int		nbr_pipes;
// 	// char	*final_infile;
// 	// char	*final_outfile;
// 	// char	*final_in_red;
// 	// char	*final_out_red;
// }					t_exec;

#endif
