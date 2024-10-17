/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:39:05 by maustel           #+#    #+#             */
/*   Updated: 2024/10/17 18:14:27 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	pipe_child_write(t_command *cmd, char **envp, int (*fd)[2], t_exec *test)
{
	int	i;

	if (cmd->id != 0 && test->final_infile == NULL)
	{
		if (dup2(fd[cmd->id - 1][0], 0) == -1)
			printf("dup2 failed write");
	}

	// if (close(fd[cmd->id - 1][0]) == -1)		//close read
	// 	printf("close fd failed write");

	if (cmd->id != test->nbr_pipes && test->final_outfile == NULL)		//write
	{
		if (dup2(fd[cmd->id][1], 1) == -1)
		{
			exit (print_error(errno, NULL, test));
			printf("dup2 failed write");
		}
	}
	// if (close(fd[cmd->id][1]) == -1)			//close write
	// 	printf("close fd failed write");

	i = 0;
	while (i <= test->nbr_pipes)
	{
		if (close(fd[i][0]) == -1)		//close read
			printf("close fd failed write");
		if (close(fd[i][1]) == -1)			//close write
			printf("close fd failed write");
		i++;
	}
	execve(cmd->path, cmd->args, envp);
	printf("execve failed\n");
	exit(1);
}

// void	pipe_child_read(t_command *cmd, char **envp, int (*fd)[2], t_exec *test)
// {
// 	if (close(fd[0][1]) == -1)
// 		printf("close fd failed write");
// 	if (test->final_infile == NULL)
// 	{
// 		if (dup2(fd[0][0], 0) == -1)
// 			printf("dup2 failed write");
// 	}
// 	if (close(fd[0][0]) == -1)
// 		printf("close fd failed write");
// 	execve(cmd->path, cmd->args, envp);
// 	printf("execve failed\n");
// }

int	execute_pipe(char **envp, t_list *structi, t_exec *test)
{
	int		fd[test->nbr_pipes][2];
	pid_t	pid[test->nbr_pipes + 1];
	t_command	*current_cmd;
	int		n;

	n = 0;
	while (structi != NULL)
	{
		printf("%d\n", n);
		current_cmd = (t_command*) structi->content;
		current_cmd->id = n;
		if (handle_stuff(envp, current_cmd, test))
			return (1);
		if (n < test->nbr_pipes)
		{
			if (pipe(fd[n]) == -1)
				return (printf("pipe failed!\n")); //errorhandling
		}
		pid[n] = fork();
		if (pid[n] == -1)
			return (print_error(errno, NULL, test));
		if (pid[n] == 0)
			pipe_child_write(current_cmd, envp, fd, test);
		structi = structi->next;
		n++;
	}

	int i = 0;
	while (i < test->nbr_pipes)
	{
		if (close(fd[i][0]) == -1)		//close read
			printf("close fd failed");
		if (close(fd[i][1]) == -1)			//close write
			printf("close fd failed");
		i++;
	}

	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);

	return (0);
}

// int main(int ergc, char **argv, char **envp)
// {
// 	execute_pipe(envp, NULL, NULL);
// 	return (0);
// }

