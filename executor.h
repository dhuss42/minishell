/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:59:19 by maustel           #+#    #+#             */
/*   Updated: 2024/11/18 11:41:16 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "./libft/libft.h"
# include "minishell_eichhoernchen.h"

# ifndef BASE_PATH
#  define BASE_PATH "executor/tmp/heredoc_temp"
# endif

typedef enum e_custom_err
{
	E_CUSTOM_ARGC = 107,
	E_PATH,
	E_FILENOEXIST,
	E_NOPERMISSION,
	E_CMD_ISDIRECTORY,
	E_FILE_ISDIRECTORY,
	E_TOOMANYARG,
	E_NOCLOSINGQUOTE,
	E_NOTSET,
	E_CDNOSUCHFOD,
	E_INIT_TERMINAL,
	E_PARENT,
	E_BUILTIN,
	E_NOTVALIDIDENT,
	E_SIGINT = 130,
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


//-----------------executor-----------------------
char	*get_path(char *cmd, char **envp);
void	free_paths(char **split_paths, char **append);
// int		print_error(int err_no, char *str, int print);
int		check_files(t_command *row);
int		exec_redirections(t_command *row);
void	free_double(char **to_free);
int		free_row(t_command *example);
// int		execute_pipechain(char **envp, t_list *table, int nbr_pipes, t_shell *shell);
int		handle_stuff(char **envp, t_command *row);
int		get_check_path(t_command *row, char **envp);
int		free_table(t_list *table);
int		handle_heredoc(t_list *table, char **env);
int		heredoc_expansion(char *line, char **env);
int		redirect_input(t_command row, int *fd);
int		redirect_output(t_command row, int *fd);
void	reset_redirections(t_command row);
int		executor(char **envp, t_list *table, t_shell *shell);
int		pipechain_loop(t_list *table, pid_t *pid, int (*fd)[2], t_shell *shell);
int		pipe_parent(pid_t *pid, int (*fd)[2], t_list *table, int nbr_pipes);
void	free_child_exit(t_shell *shell, int exit_code);

//-------------signals---------
void	handle_signals(int is_child);
void	init_terminal(void);

#endif
