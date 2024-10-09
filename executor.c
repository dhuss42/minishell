/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:59:17 by maustel           #+#    #+#             */
/*   Updated: 2024/10/09 17:07:54 by maustel          ###   ########.fr       */
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
int	parent_function(pid_t id, t_exec *test)
{
	int	wstatus;
	int	exit_code;

	if (waitpid(id, &wstatus, 0) == -1)
		return (print_error(E_PARENT, NULL, test));
	if (WIFEXITED(wstatus))	//if programm exited normally
		exit_code = WEXITSTATUS(wstatus);	//exit_code = value with which the programm exited
	else
		return (print_error(E_PARENT, NULL, test));
	test->exit_code = exit_code;
	return (exit_code);
}

//when file not exists ./"filename"--> "No such file or directory", Errorcode: 127
//when no permission for binary file--> "Permission denied", Errorcode: 126
//when command does not exist-->"command not found", errorcode: 127

int	execute_single_command(char **envp, t_command example, t_exec *test)
{
	pid_t	id;
	char	*path;

	// if (is_built_in)
	// 	ecexute_builtin();
	if (handle_redirections(example, test))
		return (1);
	path = get_path(example.args[0], envp);
	if (!path)
		return (print_error(E_PATH, NULL, test));
	// if (access(path, F_OK) == -1)
	// {
	// 	printf("FILENOTEXIST");
	// 	free(path);
	// 	return (print_error(127, example.args[0], test));	/////
	// }
	id = fork();
	if (id == -1)
		return (print_error(errno, NULL, test));
	else if (id == 0)
	{
		if (execve(path, example.args, envp))
		{
			if (path)
				free (path);
			exit (print_error(127, example.args[0], test));
		}
	}
	else if (id > 0)
		parent_function(id, test);
	if (path)
		free (path);
	return (test->exit_code);
}

int	free_all(t_command *example)
{
	if (example->args)
		free_double(example->args);
	if (example->filename)
		free_double(example->filename);
	if (example->red_symbol)
		free_double(example->red_symbol);
	return (1);
}

int	executor(char **envp, t_command example, t_exec *test)
{
	//check if nbr_pipes == 0
	if (execute_single_command(envp, example, test))
		return (free_all(&example)); // freeeee
	// else
	// 	pipechain(envp, args);
	return (test->exit_code);
}

void	create_examples(t_command *ex)
{
	ex->args = malloc(sizeof(char*) * 10);
	ex->args[0] = ft_strdup("/Users/maustel/Projects/minishell/a.out2");
	// ex->args[1] = ft_strdup("Hallo du");
	ex->args[1] = NULL;
	// ex->args[1] = ft_strdup("-l");
	// ex->args[2] = ft_strdup("libft");
	// ex->args[3] = NULL;
	// ex->filename = malloc(sizeof(char*) * 10);
	// ex->filename[0] = ft_strdup("out7");
	// ex->filename[1] = ft_strdup("in1");
	// ex->filename[2] = ft_strdup("out2");
	// ex->filename[3] = NULL;
	// ex->red_symbol = malloc(sizeof(char*) * 10);
	// ex->red_symbol[0] = ft_strdup(">");
	// ex->red_symbol[1] = ft_strdup("<");
	// ex->red_symbol[2] = ft_strdup(">");
	// ex->red_symbol[3] = NULL;

	ex->filename = NULL;
	ex->red_symbol = NULL;
}




int main (int argc, char **argv, char **envp)
{
	// char *args[] = {"lsa", "-la", NULL};
	t_exec test;
	t_command example;
	// int	result;

	create_examples(&example);
	test.exit_code = 0;
	if (executor (envp, example, &test))
		return (1);
	// printf ("[Exit code: %d]\n", test.exit_code);
	// printf ("[final infile: %s]\n", test.final_infile);
	// printf ("[final outfile: %s]\n", test.final_outfile);
	// printf ("[final in red: %s]\n", test.final_in_red);
	// printf ("[final out red: %s]\n", test.final_out_red);
	free_all(&example);
	return (test.exit_code);
	(void)argc;
	(void)argv;
	return (0);
}
