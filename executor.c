/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:59:17 by maustel           #+#    #+#             */
/*   Updated: 2024/10/25 09:55:37 by maustel          ###   ########.fr       */
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
	if (exit_code > 1)	//check if thats right
		return(print_error(exit_code, cmd, PRINT));
	if (exit_code == 1)
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
		return (1);	//free and close files
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
/*
!!! initialize everyting in beginning before lexer
*/
t_list	*create_example(char *args, char* red, char *files)
{
	t_list	*new;
	t_command *ex = malloc(sizeof(t_command));

	ex->args = NULL;
	ex->filename = NULL;
	ex->red_symbol = NULL;
	ex->path = NULL;
	ex->heredoc_file_path = NULL;
	ex->args = ft_split(args, ' ');
	ex->filename = ft_split(files, ' ');
	ex->red_symbol = ft_split(red, ' ');
	new = ft_lstnew((void *) ex);
	return (new);
}

int main (int argc, char **argv, char **envp)
{
	t_exec test;
	t_list *table;
	// t_command	*current_cmd;
	table = NULL;
	t_list	*second = NULL;
	t_list	*third = NULL;
	t_list	*fourth = NULL;

	table = create_example("echo outiout", ">", "out");
	second = create_example("grep a", "<", "libft");
	ft_lstadd_back(&table, second);
	third = create_example("cat", "<", "libft");
	ft_lstadd_back(&table, third);
	fourth = create_example("grep a", "<", "libft");
	ft_lstadd_back(&table, fourth);
	// current_cmd = (t_command *) temp->content;
	// printf("temp\nargs: %s\nfiles: %s\nsymbol: %s\n\n", current_cmd->args[0], current_cmd->filename[0], current_cmd->red_symbol[0]);
	// current_cmd = (t_command *) table->content;
	// printf("table\nargs: %s\nfiles: %s\nsymbol: %s\n\n", current_cmd->args[0], current_cmd->filename[0], current_cmd->red_symbol[0]);

	if (executor (envp, table, &test))
		return (print_error(0, NULL, NOTPRINT));
	// printf ("[Exit code: %d]\n", test.exit_code);
	// printf ("[final infile: %s]\n", test.final_infile);
	// printf ("[final outfile: %s]\n", test.final_outfile);
	// printf ("[final in red: %s]\n", test.final_in_red);
	// printf ("[final out red: %s]\n", test.final_out_red);
	free_table(table);
	return (print_error(0, NULL, NOTPRINT));
	(void)argc;
	(void)argv;
	return (0);
}

