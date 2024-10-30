/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:59:19 by maustel           #+#    #+#             */
/*   Updated: 2024/10/02 15:10:48 by maustel          ###   ########.fr       */
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
	E_CUSTOM_ARGC = 1
}			t_custom_err;

typedef struct s_get_path
{
	char	*big_path;
	char	**split_paths;
	char	**append;
	char	*move;
	char	*path;
}	t_get_path;

char	*get_path(char *cmd, char **envp);

#endif