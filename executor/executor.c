/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:59:17 by maustel           #+#    #+#             */
/*   Updated: 2024/11/26 15:53:18 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*-------------------------------------------------------------
Handle pipechain
---------------------------------------------------------------*/
int	execute_pipechain(t_list *table, int nbr_pipes, t_shell *shell)
{
	int		fd[nbr_pipes][2];
	pid_t	pid[nbr_pipes + 1];
	int		n;

	n = 0;
	while (n < nbr_pipes)
	{
		if (pipe(fd[n]) == -1)
			return (print_error(errno, NULL, PRINT));
		n++;
	}
	if (pipechain_loop(table, pid, fd, shell))
		return (1);
	if (pipe_parent(pid, fd, table, nbr_pipes))
		return (2);
	return (0);
}

/*-------------------------------------------------------------
Handle parent for single command
waitpid() blocks until the child process terminates or until a signal occurs
WIFEXITED(wstatus) macro checks if the process exited normally
WEXITwSTATUS(wstatus) extracts the exit wstatus value from the wstatus argument
if (WIFSIGNALED(wstatus)): if interrupted with signal
---------------------------------------------------------------*/
int	single_parent(pid_t id, char *cmd)
{
	int	wstatus;
	int	exit_code;

	exit_code = 0;
	if (waitpid(id, &wstatus, 0) == -1)
		return (1);
	if (WIFEXITED(wstatus))
		exit_code = WEXITSTATUS(wstatus);
	if (WIFSIGNALED(wstatus))
		exit_code = WTERMSIG(wstatus) + 128;
	if (exit_code > 0)
		return (print_error(exit_code, cmd, NOTPRINT));
	return (exit_code);
}

/*-------------------------------------------------------------
Handle child for single command
if execve fails, its because of command not found (127)
child then exits with 127 and the parent will store the exit state
if it doesnt fail, exit code is 0
---------------------------------------------------------------*/
void	single_child(char *path, char **envp, t_command *row, t_shell *shell)
{
	if (execve(path, row->args, envp))
	{
		print_error(127, row->args[0], PRINT);
		free_child_exit(shell, 127);
	}
}

/*-------------------------------------------------------------
execute single command without pipe
---------------------------------------------------------------*/
int	execute_single_command(char **envp, t_command *row, t_shell *shell)
{
	pid_t	id;

	if (check_files(row))
		return (1);
	if (exec_redirections(row))
		return (2);
	if (check_builtins(shell, row) < 1)
		return (0);
	if (get_check_path(row, envp))
		return (3);
	if (row->args[0])
	{
		id = fork();
		if (id == -1)
			return (print_error(errno, NULL, PRINT));
		else if (id == 0)
			single_child(row->path, envp, row, shell);
		else if (id > 0)
		{
			if (single_parent(id, row->args[0]))
				return (2);
		}
	}
	reset_redirections(*row);
	return (0);
}

/*-------------------------------------------------------------
Main function for executor
---------------------------------------------------------------*/
int	executor(char **envp, t_list *table, t_shell *shell)
{
	t_command	*current_cmd;
	int			nbr_pipes;

	if (shell->syntax_error == true)
		return (1);
	if (handle_heredoc(table, envp))
		return (2);
	handle_signals(1);
	nbr_pipes = ft_lstsize(table) - 1;
	if (nbr_pipes == 0)
	{
		current_cmd = (t_command *) table->content;
		if (execute_single_command(envp, current_cmd, shell))
		{
			reset_redirections(*current_cmd);
			return (3);
		}
	}
	else if (nbr_pipes > 0)
	{
		if (execute_pipechain(table, nbr_pipes, shell))
			return (4);
	}
	return (0);
}
