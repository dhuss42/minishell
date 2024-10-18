/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:39:05 by maustel           #+#    #+#             */
/*   Updated: 2024/10/18 12:36:37 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	close_fds(int (*fd)[2], int id, int nbr_pipes)
{
	int	i;

	i = 0;
	while (i < nbr_pipes)
	{
		if (id == 0 || i != id - 1)
		{
			if (close(fd[i][0]) == - 1)		//close read
				printf("close fd[%d][0] failed read\n", i);
		}
		if (i != id)
		{
			if (close(fd[i][1]) == - 1)			//close write
				printf("close fd[%d][1] failed write\n", i);
		}
		i++;
	}
	return (0);
}

int	close_fds_parent(int (*fd)[2], int nbr_pipes)
{
	int	i;

	i = 0;
	while (i < nbr_pipes)
	{
		if (close(fd[i][0]) == - 1)		//close read
			printf("close fd[%d][10] failed read\n", i);
		if (close(fd[i][1]) == - 1)			//close write
			printf("close fd[%d][1] failed write\n", i);
		i++;
	}
	return (0);
}

void	pipe_child(t_command *cmd, char **envp, int (*fd)[2], t_exec *test)
{
	if (close_fds(fd, cmd->id, test->nbr_pipes))
		exit (1);	//todo errno
	if (cmd->id != 0 && test->final_infile == NULL)
	{
		if (dup2(fd[cmd->id - 1][0], 0) == - 1)
			printf("dup2 fd[%d][1] failed \n", cmd->id);
		if (close(fd[cmd->id - 1][0]) == - 1)		//close read
			printf("close fd[%d][0] failed read\n", cmd->id - 1);
	}
	if (cmd->id != test->nbr_pipes && test->final_outfile == NULL)		//write
	{
		if (dup2(fd[cmd->id][1], 1) == - 1)
		{
			exit (print_error(errno, NULL, test));
			printf("dup2 failed write\n");
		}
		if (close(fd[cmd->id][1]) == - 1)			//close write
			printf("close fd[%d][1] failed write\n", cmd->id);
	}
	execve(cmd->path, cmd->args, envp);
	printf("execve failed\n");
	exit(1);
}

int	execute_pipe(char **envp, t_list *structi, t_exec *test)
{
	int		fd[test->nbr_pipes][2];
	pid_t	pid[test->nbr_pipes + 1];
	t_command	*current_cmd;
	int		n;

	n = 0;
	while (n < test->nbr_pipes)
	{
		if (pipe(fd[n]) == -1)
			return (printf("pipe failed!\n")); //errorhandling
		n++;
	}
	n = 0;
	while (structi != NULL)
	{
		current_cmd = (t_command*) structi->content;
		current_cmd->id = n;
		if (handle_stuff(envp, current_cmd, test))
			return (1);
		pid[n] = fork();
		if (pid[n] == -1)
			return (print_error(errno, NULL, test));
		if (pid[n] == 0)
			pipe_child(current_cmd, envp, fd, test);
		structi = structi->next;
		n++;
	}
	if (close_fds_parent(fd, test->nbr_pipes))
		return (1); //todo
	int i = 0;
	while (i <= test->nbr_pipes)
	{
		waitpid(pid[i], NULL, 0);	//todo: safe exit_code
		i++;
	}
	return (0);
}

// int main(int ergc, char **argv, char **envp)
// {
// 	execute_pipe(envp, NULL, NULL);
// 	return (0);
// }

