/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:39:05 by maustel           #+#    #+#             */
/*   Updated: 2024/10/16 16:14:18 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

//IN CHILD:
	// t_command	*current_cmd;
	// 	char	*path;
	// current_cmd = (t_command*) structi->content;
	// if (handle_stuff(current_cmd, test))
	// 	return (1);
	// path = get_check_path(current_cmd->args[0], envp, test);
	// if (!path)
	// 	return (2);

int	execute_pipe(char **envp, t_list *structi, t_exec *test)
{
	pid_t	id;
	int		fd[2];

	if (pipe(fd) == -1)
		return (1); //errorhandling
	


}