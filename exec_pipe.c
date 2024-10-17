/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:39:05 by maustel           #+#    #+#             */
/*   Updated: 2024/10/17 13:04:00 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	pipe_child_write(char *path, t_command *cmd, char **envp, int *fd)
{
	if (close(fd[0]) == -1)
		printf("close fd failed write");
	if (dup2(fd[1], 1) == -1)
		printf("dup2 failed write");
	if (close(fd[1]) == -1)
		printf("close fd failed write");
	execve(path, cmd->args, envp); //maybe safe path in cmd->path??
	printf("execve failed\n");
	exit(1);
}

void	pipe_child_read(char *path, t_command *cmd, char **envp, int *fd)
{
	if (close(fd[1]) == -1)
		printf("close fd failed write");
	if (dup2(fd[0], 0) == -1)
		printf("dup2 failed write");
	if (close(fd[0]) == -1)
		printf("close fd failed write");
	execve(path, cmd->args, envp); //maybe safe path in cmd->path??
	printf("execve failed\n");
}

// int	first_cmd(t_list *structi, char **envp, t_exec *test, int *fd)
// {

// 	else if (pid == 0)
// 		pipe_child_write(path, current_cmd, envp, test, fd);
// 	else if (pid > 0)
// 	{
// 		waitpid(pid, NULL, 0);
// 	}
// 	return (0);
// }

int	execute_pipe(char **envp, t_list *structi, t_exec *test)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	char	*path;
	t_command	*current_cmd;

	current_cmd = (t_command*) structi->content;
	if (handle_stuff(*current_cmd, test))
		return (1);
	path = get_check_path(current_cmd->args[0], envp, test);
	if (!path)
		return (2);
	if (pipe(fd) == -1)
		return (printf("pipe failed!\n")); //errorhandling
	pid1 = fork();
	if (pid1 == -1)
		return (print_error(errno, NULL, test));
	if (pid1 == 0)
		pipe_child_write(path, current_cmd, envp, fd);

	structi = structi->next;
	current_cmd = (t_command*) structi->content;
	if (handle_stuff(*current_cmd, test))
		return (1);
	path = get_check_path(current_cmd->args[0], envp, test);
	if (!path)
		return (2);
	pid2 = fork();
	if (pid2 == -1)
		return (print_error(errno, NULL, test));
	if (pid2 == 0)
		pipe_child_read(path, current_cmd, envp, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	// pid_t	pid1;
	// pid_t	pid2;
	// char **args1 = ft_split("echo david\nis\nhere", ' ');
	// char **args2 = ft_split("grep i", ' ');

	// pid1 = fork();
	// if (pid1 < 0)
	// 	return (printf("forking failed\n"));
	// if (pid1 == 0)
	// {
	// 	close(fd[0]);
	// 	dup2(fd[1], 1);
	// 	close(fd[1]);
	// 	execve("/usr/bin/echo", args1, envp);
	// 	printf("execve failed\n");
	// 	exit(1);
	// }
	// pid2 = fork();
	// if (pid2 == -1)
	// 	return (printf("forking failed\n"));
	// if (pid2 == 0)
	// {
	// 	close(fd[1]);
	// 	dup2(fd[0], 0);
	// 	close(fd[0]);
	// 	execve("/usr/bin/grep", args2, envp);
	// }
	// close(fd[0]);
	// close(fd[1]);
	// waitpid(pid1, NULL, 0);
	// waitpid(pid2, NULL, 0);

	return (0);
}

// int main(int ergc, char **argv, char **envp)
// {
// 	execute_pipe(envp, NULL, NULL);
// 	return (0);
// }

