/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:59:17 by maustel           #+#    #+#             */
/*   Updated: 2024/10/25 14:55:30 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/*-------------------------------------------------------------
Handle parent for single command
waitpid() blocks until the child process terminates or until a signal occurs
WIFEXITED(wstatus) macro checks if the process exited normally
WEXITwSTATUS(wstatus) extracts the exit wstatus value from the wstatus argument
---------------------------------------------------------------*/
int	single_parent(pid_t id, char* cmd)
{
	int	wstatus;
	int	exit_code;

	exit_code = 0;
	if (waitpid(id, &wstatus, 0) == -1)
		return (print_error(E_PARENT, NULL, PRINT));
	if (WIFEXITED(wstatus))
			exit_code = WEXITSTATUS(wstatus);
	else
		return (print_error(E_PARENT, NULL, PRINT));
	if (exit_code > 0)	//check if thats right
		return(print_error(exit_code, cmd, NOTPRINT));
	return (exit_code);
}

/*-------------------------------------------------------------
Handle child for single command
if execve fails, its because of command not found (127)
child then exits with 127 and the parent will store the exit state
if it doesnt fail, exit code is 0
---------------------------------------------------------------*/
void	single_child(char *path, char **envp, t_command row)
{
	if (execve(path, row.args, envp))
		{
			free_row(&row);
			exit (127);
		}
}

/*-------------------------------------------------------------
execute single command without pipe
---------------------------------------------------------------*/
int	execute_single_command(char **envp, t_command *row)
{
	pid_t	id;

	if (exec_redirections(row))
		return (1);
	id = fork();
	if (id == -1)
		return (print_error(errno, NULL, PRINT));
	else if (id == 0)
		single_child(row->path, envp, *row);
	else if (id > 0)
	{
		if (single_parent(id, row->args[0]))
			return (1);
	}
	return (0);
}

/*-------------------------------------------------------------
Main function for executor
---------------------------------------------------------------*/
int	executor(char **envp, t_list *table, t_exec *test)
{
	t_command	*current_cmd;

	if (handle_stuff(envp, table))
		return (free_table(table));
	test->nbr_pipes = ft_lstsize(table) - 1;
	if (test->nbr_pipes == 0)
	{
		current_cmd = (t_command*) table->content;
		if (execute_single_command(envp, current_cmd))
			return (free_row(current_cmd));
	}
	else if (test->nbr_pipes > 0)
	{
		if (execute_pipechain(envp, table, test))
			return (free_table(table));
	}
	return (0);
}
