/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:39:05 by maustel           #+#    #+#             */
/*   Updated: 2024/10/22 13:49:59 by maustel          ###   ########.fr       */
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
why extra exit code and not directly test->exit_code??
---------------------------------------------------------------*/
int	pipe_parent(pid_t *pid, int (*fd)[2], t_exec *test, t_list *table)
{
	int	wstatus;
	int	exit_code;
	t_list	*tmp;
	t_command	*row;

	if (close_fds(fd, -1, test->nbr_pipes))
		exit (print_error(errno, NULL, test));
	tmp = table;
	exit_code = 0;
	int i = 0;
	while (i <= test->nbr_pipes)
	{
		if (waitpid(pid[i], &wstatus, 0) == -1)
			return (print_error(E_PARENT, NULL, test));
		if (WIFEXITED(wstatus))
			exit_code = WEXITSTATUS(wstatus);
		else
			return (1);
			// return (print_error(E_PARENT, NULL, test));
		row = (t_command*) tmp->content;	//direkt tmp->content->args[0] uebergeben?
		if (exit_code > 1)	//check if right
			return(print_error(exit_code, row->args[0], test));
		if (exit_code == 1)
			test->exit_code = 1;	//return
		tmp = tmp->next;
		i++;
	}
	return (exit_code);
}

/*-------------------------------------------------------------
Child handler for pipechain
--test, table and envp will be in one struct
---------------------------------------------------------------*/
void	pipe_child(t_command *row, char **envp, int (*fd)[2], t_exec *test, t_list *table)
{
	// printf("%d path: %s\n", row->id, row->path);
	if (close_fds(fd, row->id, test->nbr_pipes))
		exit (print_error(errno, NULL, test));
	if (row->id != 0 && row->final_infile == NULL)
	{
		if (dup2(fd[row->id - 1][0], 0) == - 1)
			exit (print_error(errno, NULL, test));
		if (close(fd[row->id - 1][0]) == - 1)
			exit (print_error(errno, NULL, test));
	}
	if (row->id != test->nbr_pipes && row->final_outfile == NULL)
	{
		if (dup2(fd[row->id][1], 1) == - 1)
			exit (print_error(errno, NULL, test));
		if (close(fd[row->id][1]) == - 1)
			exit (print_error(errno, NULL, test));
	}
	if (execve(row->path, row->args, envp))
	{
		free_table(table);
		exit (print_error(errno, NULL, test));
	}
}

/*-------------------------------------------------------------
Loop through all the pipes
--test will be	shell->exec
--table will be	shell->table
---------------------------------------------------------------*/
int	pipechain_loop(char **envp, t_list *table, pid_t *pid, int (*fd)[2], t_exec *test)
{
	int			n;
	t_command	*row;
	t_list		*tmp;

	n = 0;
	tmp = table;
	while (tmp != NULL)
	{
		row = (t_command*) tmp->content;
		pid[n] = fork();
		if (pid[n] == -1)
			return (print_error(errno, NULL, test));
		if (pid[n] == 0)
			pipe_child(row, envp, fd, test, table);	//fd into exec-struct?
		tmp = tmp->next;
		n++;
	}
	return (0);
}

/*-------------------------------------------------------------
Handle pipechain
---------------------------------------------------------------*/
int	execute_pipechain(char **envp, t_list *table, t_exec *test)
{
	int		fd[test->nbr_pipes][2];
	pid_t	pid[test->nbr_pipes + 1];
	int		n;

	n = 0;
	while (n < test->nbr_pipes)
	{
		if (pipe(fd[n]) == -1)
			return (print_error(errno, NULL, test)); //errorhandling
		n++;
	}
	if (pipechain_loop(envp, table, pid, fd, test))
		return (test->exit_code); //close fds? free?

	pipe_parent(pid, fd, test, table);
	return (test->exit_code);
}
