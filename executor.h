/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:59:19 by maustel           #+#    #+#             */
/*   Updated: 2024/10/10 12:40:05 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <stdlib.h>
#include <errno.h>

#include "./libft/libft.h"

typedef enum e_custom_err
{
	E_CUSTOM_ARGC = 107,
	E_PATH,
	E_PARENT,
	E_FILENOEXIST,
	E_NOPERMISSION
}			t_custom_err;

typedef struct s_command
{
	char	**args;
	char	**filename;
	char	**red_symbol;
} t_command;

typedef struct	s_exec
{
	int	exit_code;
	char*	final_infile;
	char*	final_outfile;
	char*	final_in_red;
	char*	final_out_red;
}					t_exec;

// typedef struct s_get_path
// {
// 	char	*big_path;
// 	char	**split_paths;
// 	char	**append;
// 	char	*move;
// 	// char	*path;
// }	t_get_path;

char	*get_path(char *cmd, char **envp);
void	free_paths(char **split_paths, char **append);
int		print_error(int err_no, char *str, t_exec *test);
int		check_redirections(t_command example, t_exec *test);
int		handle_redirections(t_command example, t_exec *test);
void	free_double(char **to_free);
int		free_all(t_command *example);

#endif
