/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:59:17 by maustel           #+#    #+#             */
/*   Updated: 2024/10/21 16:19:12 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/*-------------------------------------------------------------
Handle parent for single command
waitpid() blocks until the child process terminates or until a signal occurs
WIFEXITED(wstatus) macro checks if the process exited normally
WEXITwSTATUS(wstatus) extracts the exit wstatus value from the wstatus argument

why extra exit code and not directly test->exit_code??
---------------------------------------------------------------*/
int	single_parent(pid_t id, char* cmd, t_exec *test)
{
	int	wstatus;
	int	exit_code;

	exit_code = 0;
	if (waitpid(id, &wstatus, 0) == -1)
		return (print_error(E_PARENT, NULL, test));
	if (WIFEXITED(wstatus))
			exit_code = WEXITSTATUS(wstatus);
	else
		return (print_error(E_PARENT, NULL, test));
	if (exit_code > 1)	//check if thats right
		return(print_error(exit_code, cmd, test));
	if (exit_code == 1)
		test->exit_code = 1;
	return (exit_code);
}

/*-------------------------------------------------------------
Handle child for single command
if execve fails, its because of command not found (127)
child then exits with 127 and the parent will store the exit state
if it doesnt fail, exit code is 0
---------------------------------------------------------------*/
void	single_child(char *path, char **envp, t_command example)
{
	if (execve(path, example.args, envp))
		{
			free_row(&example);
			exit (127);
		}
}

/*-------------------------------------------------------------
execute single command without pipe
---------------------------------------------------------------*/
int	execute_single_command(char **envp, t_command *example, t_exec *test)
{
	pid_t	id;

	if (handle_stuff(envp, example, test))	//rm
		return (1);
	id = fork();
	if (id == -1)
		return (print_error(errno, NULL, test));
	else if (id == 0)
		single_child(example->path, envp, *example);
	else if (id > 0)
		single_parent(id, example->args[0], test);
	return (test->exit_code);
}

/*-------------------------------------------------------------
Main function for executor
---------------------------------------------------------------*/
int	executor(char **envp, t_list *structi, t_exec *test)
{
	t_command	*current_cmd;

	//handle stuff(strcuti)
	test->nbr_pipes = ft_lstsize(structi) - 1;
	if (test->nbr_pipes == 0)
	{
		current_cmd = (t_command*) structi->content;
		if (execute_single_command(envp, current_cmd, test))	//create function for this
		{
			if (access("tmp/heredoc_temp", F_OK) == 0)		//for each row in table
			{
				if (unlink("tmp/heredoc_temp"))
					print_error(errno, NULL, test);
			}
			return (free_row(current_cmd));
		}
	}
	else if (test->nbr_pipes > 0)
	{
		if (execute_pipechain(envp, structi, test))
		{
			if (access("tmp/heredoc_temp", F_OK) == 0)
			{
				if (unlink("tmp/heredoc_temp"))
					print_error(errno, NULL, test);
			}
			return (free_table(structi));
		}
	}
	if (access("tmp/heredoc_temp", F_OK) == 0)
	{
		if (unlink("tmp/heredoc_temp"))
			print_error(errno, NULL, test);
	}
	return (test->exit_code);
}

t_list	*create_example(char *args, char* red, char *files)
{
	t_list	*new;
	t_command *ex = malloc(sizeof(t_command));

	ex->args = NULL;
	ex->filename = NULL;
	ex->red_symbol = NULL;
	ex->path = NULL;
	ex->args = ft_split(args, ' ');
	ex->filename = ft_split(files, ' ');
	ex->red_symbol = ft_split(red, ' ');
	new = ft_lstnew((void *) ex);
	return (new);
}

int main (int argc, char **argv, char **envp)
{
	t_exec test;
	// t_command	*current_cmd;
	t_list	*structi = NULL;
	// t_list	*second = NULL;
	// t_list	*third = NULL;
	// t_list	*fourth = NULL;
	// t_list	*temp = NULL;

	structi = create_example("grep o", "<", "libft");
	// second = create_example("grep o", "", "");
	// ft_lstadd_back(&structi, second);
	// third = create_example("grep exec", "", "");
	// ft_lstadd_back(&structi, third);
	// fourth = create_example("grep free", "<", "libft");
	// ft_lstadd_back(&structi, fourth);
	// current_cmd = (t_command *) temp->content;
	// printf("temp\nargs: %s\nfiles: %s\nsymbol: %s\n\n", current_cmd->args[0], current_cmd->filename[0], current_cmd->red_symbol[0]);
	// current_cmd = (t_command *) structi->content;
	// printf("structi\nargs: %s\nfiles: %s\nsymbol: %s\n\n", current_cmd->args[0], current_cmd->filename[0], current_cmd->red_symbol[0]);
	test.exit_code = 0;
	if (executor (envp, structi, &test))
		return (test.exit_code);
	// printf ("[Exit code: %d]\n", test.exit_code);
	// printf ("[final infile: %s]\n", test.final_infile);
	// printf ("[final outfile: %s]\n", test.final_outfile);
	// printf ("[final in red: %s]\n", test.final_in_red);
	// printf ("[final out red: %s]\n", test.final_out_red);
	free_table(structi);
	return (test.exit_code);
	(void)argc;
	(void)argv;
	return (0);
}

