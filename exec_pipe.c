/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:39:05 by maustel           #+#    #+#             */
/*   Updated: 2024/10/25 16:35:03 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/*-------------------------------------------------------------
Close all opened filedescriptors from piping, we won't need
---------------------------------------------------------------*/
int	close_fds(int (*fd)[2], int id, int nbr_pipes)
{
	int	i;

	i = 0;
	while (i < nbr_pipes)
	{
		if (id == 0 || i != id - 1)
		{
			if (close(fd[i][0]) == - 1)
				return (errno);
		}
		if (i != id)
		{
			if (close(fd[i][1]) == - 1)
				return (errno);
		}
		i++;
	}
	return (0);
}

/*-------------------------------------------------------------
Parent handler for pipechain
---------------------------------------------------------------*/
int	pipe_parent(pid_t *pid, int (*fd)[2], t_list *table, int nbr_pipes)
{
	int	wstatus;
	int	exit_code;
	t_list	*tmp;
	t_command	*row;

	if (close_fds(fd, -1, nbr_pipes))
		exit (print_error(errno, NULL, PRINT));
	tmp = table;
	exit_code = 0;
	int i = 0;
	while (i <= nbr_pipes)
	{
		if (waitpid(pid[i], &wstatus, 0) == -1)
			return (print_error(E_PARENT, NULL, PRINT));
		if (WIFEXITED(wstatus))
			exit_code = WEXITSTATUS(wstatus);
		else
			return (print_error(E_PARENT, NULL, PRINT));
		row = (t_command*) tmp->content;
		if (exit_code > 0)	//check if right
			return(print_error(exit_code, row->args[0], NOTPRINT));
		tmp = tmp->next;
		i++;
	}
	return (exit_code);
}

int	duplicate_fd(t_command *row, int (*fd)[2], int nbr_pipes)
{
	if (row->id != 0 && row->final_infile == NULL)
	{
		if (dup2(fd[row->id - 1][0], 0) == - 1)
			exit (print_error(errno, NULL, PRINT));
		if (close(fd[row->id - 1][0]) == - 1)
			exit (print_error(errno, NULL, PRINT));
	}
	if (row->final_infile)
	{
		if (redirect_input(*row, &fd[row->id - 1][0]))
			exit(errno);	//exit with exit code
	}
	if (row->id != nbr_pipes && row->final_outfile == NULL)
	{
		if (dup2(fd[row->id][1], 1) == - 1)
			exit (print_error(errno, NULL, PRINT));
		if (close(fd[row->id][1]) == - 1)
			exit (print_error(errno, NULL, PRINT));
	}
	if (row->final_outfile)
	{
		if (redirect_output(*row, &fd[row->id][1]))
			exit (errno);		//exit with exit_code
	}
	return (0);
}

/*-------------------------------------------------------------
Child handler for pipechain
---------------------------------------------------------------*/
void	pipe_child(t_command *row, char **envp, int (*fd)[2], t_list *table)
{
	int	nbr_pipes;

	nbr_pipes = ft_lstsize(table) - 1;
	if (close_fds(fd, row->id, nbr_pipes))
		exit (print_error(errno, NULL, PRINT));
	if (duplicate_fd(row, fd, nbr_pipes))
		exit(errno);
	// if (duplicate_fd(row, &fd[row->id][1], STDOUT_FILENO))
	// 	exit(errno);
	if (execve(row->path, row->args, envp))
	{
		free_table(table);
		exit (print_error(errno, NULL, PRINT));
	}
}

/*-------------------------------------------------------------
Loop through all the pipes
---------------------------------------------------------------*/
int	pipechain_loop(char **envp, t_list *table, pid_t *pid, int (*fd)[2])
{
	int			n;
	t_command	*row;
	t_list		*tmp;

	n = 0;
	tmp = table;
	while (tmp != NULL)
	{
		row = (t_command*) tmp->content;
		if (handle_stuff(envp, row))
			return (1);
		pid[n] = fork();
		if (pid[n] == -1)
			return (print_error(errno, NULL, PRINT));
		if (pid[n] == 0)
			pipe_child(row, envp, fd, table);	//fd into exec-struct?
		tmp = tmp->next;
		n++;
	}
	return (0);
}

/*-------------------------------------------------------------
Handle pipechain
---------------------------------------------------------------*/
int	execute_pipechain(char **envp, t_list *table, int nbr_pipes)
{
	int		fd[nbr_pipes][2];
	pid_t	pid[nbr_pipes + 1];
	int		n;

	n = 0;
	while (n < nbr_pipes)
	{
		if (pipe(fd[n]) == -1)
			return (print_error(errno, NULL, PRINT)); //errorhandling
		n++;
	}
	if (pipechain_loop(envp, table, pid, fd))
		return (1); //close fds? free?

	if (pipe_parent(pid, fd, table, nbr_pipes))
		return (2);
	return (0);
}
