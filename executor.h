/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:59:19 by maustel           #+#    #+#             */
/*   Updated: 2024/10/08 10:42:11 by maustel          ###   ########.fr       */
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
	E_PARENT
}			t_custom_err;

typedef struct	s_arguments
{
	char	**args;
	char	**filenames;
	char	**redir_symbol;
}					t_arguments;

typedef struct	s_exec
{
	int	exit_code;
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
int		print_error(int err_no, char *str);

#endif
