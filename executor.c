/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:59:17 by maustel           #+#    #+#             */
/*   Updated: 2024/10/07 13:49:24 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/*
	1)	find path -> if not in PATH, maybe path already written in temrinal?
	2)	error handling (fe "command not found")
	3)	execve
*/

int	execute_single_command(char **envp, char **args)
{
	pid_t	id;
	char	*path;

	path = get_path(args[0], envp);
	if (!path)
		return (print_error(E_PATH, NULL));
	id = fork();
	if (id == -1)
		return (print_error(errno, NULL));
	else if (id == 0)
	{
		printf("Child is playing...\n"); //any code after execve in the child process wont be executed
		sleep(1);
		if (execve(path, args, envp))
		{
			print_error(127, args[0]);
			if (path)
				free (path);
			return (1);
		}
	}
	else if (id > 0)
	{
        wait(NULL);
        printf("Child process has finished.\n");
	}
	if (path)
		free (path);
	return (0);
}

int	executor(char **envp, char **args)
{
	if (1 == 1)	//check if nbr_pipes == 0
		execute_single_command(envp, args);
	// else
	// 	pipechain(envp, args);
	return (0);
}

int main (int argc, char **argv, char **envp)
{
	char *args[] = {"echt", "Amsel", "Specht", "-l", NULL};
	// t_exec test;
	// test.args[0] = ft_strdup("/bin/ls");
	// test.args[1] = ft_strdup("-la");
	// test.args[2] = NULL;
	// char *args[] = {"ls -la", NULL};

	if (executor (envp, args))
		return (1);
	(void)argc;
	(void)argv;
	return (0);
}
