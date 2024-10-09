/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:59:17 by maustel           #+#    #+#             */
/*   Updated: 2024/10/09 10:35:53 by maustel          ###   ########.fr       */
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
		exit_code = WEXITSTATUS(wstatus);	//exit_code = value with which the programm exited
	else
		return (print_error(E_PARENT, NULL));
	return (exit_code);
}

void	handle_redirections()
{

}

int	execute_single_command(char **envp, t_command example)
{
	pid_t	id;
	char	*path;
	int		exit_code = 0;

	// if (is_built_in)
	// 	ecexute_builtin();
	// if (handle_redirections(data) == ERROR)
	// 	return (free_process_exit(data));
	path = get_path(example.args[0], envp);
	if (!path)
		return (print_error(E_PATH, NULL));
	id = fork();
	if (id == -1)
		return (print_error(errno, NULL));
	else if (id == 0)
	{
		if (execve(path, example.args, envp))
		{
			if (path)
				free (path);
			exit (print_error(127, example.args[0]));
		}
	}
	else if (id > 0)
		exit_code = parent_function(id);
	if (path)
		free (path);
	return (exit_code);
}

int	executor(char **envp, t_command example, t_exec *test)
{
	//check if nbr_pipes == 0
	test->exit_code = execute_single_command(envp, example);
	// else
	// 	pipechain(envp, args);
	return (test->exit_code);
}

void	create_examples(t_command *ex)
{
	ex->args = malloc(sizeof(char*) * 10);
	ex->args[0] = ft_strdup("lsd");
	ex->args[1] = ft_strdup("-l");
	ex->args[2] = ft_strdup("libft");
	ex->args[3] = NULL;
	ex->filename = malloc(sizeof(char*) * 10);
	ex->filename[0] = ft_strdup("in1");
	ex->filename[1] = ft_strdup("out1");
	ex->filename[2] = NULL;
	ex->red_symbol = malloc(sizeof(char*) * 10);
	ex->red_symbol[0] = ft_strdup("<");
	ex->red_symbol[1] = ft_strdup(">");
	ex->red_symbol[2] = NULL;
}

int main (int argc, char **argv, char **envp)
{
	// char *args[] = {"lsa", "-la", NULL};
	t_exec test;
	t_command example;
	// int	result;

	create_examples(&example);
	test.exit_code = 0;
	executor (envp, example, &test);
	printf ("3. Exit code: %d\n", test.exit_code);
	return (test.exit_code);
	(void)argc;
	(void)argv;
	return (0);
}
