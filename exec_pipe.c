/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:39:05 by maustel           #+#    #+#             */
/*   Updated: 2024/10/18 16:29:38 by maustel          ###   ########.fr       */
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
Child handler for pipechain
--test, structi and envp will be in one struct
---------------------------------------------------------------*/
void	pipe_child(t_command *cmd, char **envp, int (*fd)[2], t_exec *test, t_list *structi)
{
	if (close_fds(fd, cmd->id, test->nbr_pipes))
		exit (print_error(errno, NULL, test));
	if (cmd->id != 0 && test->final_infile == NULL)
	{
		if (dup2(fd[cmd->id - 1][0], 0) == - 1)
			exit (print_error(errno, NULL, test));
		if (close(fd[cmd->id - 1][0]) == - 1)
			exit (print_error(errno, NULL, test));
	}
	if (cmd->id != test->nbr_pipes && test->final_outfile == NULL)
	{
		if (dup2(fd[cmd->id][1], 1) == - 1)
			exit (print_error(errno, NULL, test));
		if (close(fd[cmd->id][1]) == - 1)
			exit (print_error(errno, NULL, test));
	}
	execve(cmd->path, cmd->args, envp);
	free_table(structi);
	(void)structi;
	exit (print_error(errno, NULL, test));
}

/*-------------------------------------------------------------
Loop through all the pipes
--test will be	shell->exec
--structi will be	shell->table
---------------------------------------------------------------*/
int	pipechain_loop(char **envp, t_list *structi, pid_t *pid, int (*fd)[2], t_exec *test)
{
	int		n;
	t_command	*current_cmd;
	t_list		*temp;

	n = 0;
	temp = structi;
	while (temp != NULL)
	{
		current_cmd = (t_command*) temp->content;
		current_cmd->id = n;
		if (handle_stuff(envp, current_cmd, test))
			return (1);
		pid[n] = fork();
		if (pid[n] == -1)
			return (print_error(errno, NULL, test));
		if (pid[n] == 0)
			pipe_child(current_cmd, envp, fd, test, temp);
		temp = temp->next;
		n++;
	}
	return (0);
}

/*-------------------------------------------------------------
Parent handler for pipechain
---------------------------------------------------------------*/
int	pipe_parent(pid_t *pid, int (*fd)[2], t_exec *test, t_list *structi)
{
	int	wstatus;
	int	exit_code;
	t_list	*temp;
	t_command	*current_cmd;

	if (close_fds(fd, -1, test->nbr_pipes))
		exit (print_error(errno, NULL, test));
	temp = structi;
	exit_code = 0;
	int i = 0;
	while (i <= test->nbr_pipes)
	{
		if (waitpid(pid[i], &wstatus, 0) == -1)
			return (print_error(E_PARENT, NULL, test));
		if (WIFEXITED(wstatus))
			exit_code = WEXITSTATUS(wstatus);
		else
			return (print_error(E_PARENT, NULL, test));
		current_cmd = (t_command*) temp->content;
		if (exit_code != 0)
			return(print_error(exit_code, current_cmd->args[0], test));
		temp = temp->next;
		i++;
	}
	return (exit_code);
}

/*-------------------------------------------------------------
Handle pipechain
---------------------------------------------------------------*/
int	execute_pipechain(char **envp, t_list *structi, t_exec *test)
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
	if (pipechain_loop(envp, structi, pid, fd, test))
		return (test->exit_code); //close fds? free?

	pipe_parent(pid, fd, test, structi);
	return (test->exit_code);
}
