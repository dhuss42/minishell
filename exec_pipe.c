/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:39:05 by maustel           #+#    #+#             */
/*   Updated: 2024/10/16 17:31:38 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	pipe_child(char *path, t_command *cmd, char **envp, t_exec *test, int *fd)
{
	dup2(fd[1], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(path, cmd->args, envp); //maybe safe path in cmd->path??
}

int	first_cmd(t_list *structi, char **envp, t_exec *test, int *fd)
{
	pid_t	pid1;
	char	*path;
	t_command	*current_cmd;

	current_cmd = (t_command*) structi->content;
	if (handle_stuff(current_cmd, test))
		return (1);
	path = get_check_path(current_cmd->args[0], envp, test);
	if (!path)
		return (2);
	pid1 = fork();
	if (pid1 == -1)
		return (print_error(errno, NULL, test));
	else if (pid1 == 0)
		pipe_child(path, current_cmd, envp, test, fd);
	else if (pid1 > 0)
	{
		// parent
	}
	return (0);
}

int	execute_pipe(char **envp, t_list *structi, t_exec *test)
{
	pid_t	pid2;
	int		fd[2];

	if (pipe(fd) == -1)
		return (1); //errorhandling
	if (first_cmd(structi, envp, test, fd))
		return (2);
	if (second_cmd(structi, envp, test, fd))// todo
		return (3);

}