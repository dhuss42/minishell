/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:59:17 by maustel           #+#    #+#             */
/*   Updated: 2024/10/08 11:22:37 by maustel          ###   ########.fr       */
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
	WIFEXITED(status) macro checks if the process exited normally
	WEXITSTATUS(status) extracts the exit status value from the status argument
*/
int	parent_function(pid_t pid)
{
	int	status;
	int	exit_code;

	if (waitpid(pid, &status, 0) == -1)
		return (print_error(E_PARENT, NULL));
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else
		return (print_error(E_PARENT, NULL));
	return (exit_code);
}

int	execute_single_command(char **envp, char **args)
{
	pid_t	pid;
	char	*path;
	int		exit_code;

	// if (is_built_in)
	// 	ecexute_builtin();
	path = get_path(args[0], envp);
	if (!path)
		return (print_error(E_PATH, NULL));
	pid = fork();
	if (pid == -1)
		return (print_error(errno, NULL));
	else if (pid == 0)
	{
		if (execve(path, args, envp))
		{
			if (path)
				free (path);
			return (print_error(127, args[0]));
		}
	}
	else if (pid > 0)
		exit_code = parent_function(pid);
	printf("1. exit code: %d\n", exit_code);
	if (path)
		free (path);
	return (exit_code);
}

int	executor(char **envp, char **args, t_exec *test)
{
	//check if nbr_pipes == 0
	test->exit_code = execute_single_command(envp, args);
	printf("2. exit code: %d\n", test->exit_code);
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
