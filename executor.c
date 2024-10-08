/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:59:17 by maustel           #+#    #+#             */
/*   Updated: 2024/10/08 16:40:30 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/*
	1)	find path -> if not in PATH, maybe path already written in temrinal?
	2)	error handling (fe "command not found")
	3)	execve
*/

/*
	waitpid() blocks until the child process terminates or until a signal occur
	WIFEXITED(wstatus) macro checks if the process exited normally
	WEXITwSTATUS(wstatus) extracts the exit wstatus value from the wstatus argument
*/
int	parent_function(pid_t id)
{
	int	wstatus;
	int	exit_code;

	if (waitpid(id, &wstatus, 0) == -1)
		return (print_error(E_PARENT, NULL));
	if (WIFEXITED(wstatus))	//if programm exited normally
		exit_code = WEXITwSTATUS(wstatus);	//exit_code = value with which the programm exited
	else
		return (print_error(E_PARENT, NULL));
	return (exit_code); 
}

int	execute_single_command(char **envp, char **args)
{
	pid_t	id;
	char	*path;
	int		exit_code;

	// if (is_built_in)
	// 	ecexute_builtin();
	path = get_path(args[0], envp);
	if (!path)
		return (print_error(E_PATH, NULL));
	id = fork();
	if (id == -1)
		return (print_error(errno, NULL));
	else if (id == 0)
	{
		if (execve(path, args, envp))
		{
			if (path)
				free (path);
			exit (print_error(127, args[0]));
		}
	}
	else if (id > 0)
		exit_code = parent_function(id);
	if (path)
		free (path);
	return (exit_code);
}

int	executor(char **envp, char **args, t_exec *test)
{
	//check if nbr_pipes == 0
	test->exit_code = execute_single_command(envp, args);
	// else
	// 	pipechain(envp, args);
	return (test->exit_code);
}

int main (int argc, char **argv, char **envp)
{
	char *args[] = {"lsff", "-la", NULL};
	t_exec test;
	int	result;

	test.exit_code = 0;
	result = executor (envp, args, &test);
	printf ("3. Exit code: %d\n", test.exit_code);
	return (result);
	(void)argc;
	(void)argv;
	return (0);
}
