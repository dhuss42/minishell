/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:59:17 by maustel           #+#    #+#             */
/*   Updated: 2024/11/29 11:46:00 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*-------------------------------------------------------------
Handle pipechain
---------------------------------------------------------------*/
int	execute_pipechain(t_list *table, int nbr_pipes, t_shell *shell)
{
	int		n;

	if (init_fd_pid(shell, nbr_pipes))
		return (1);
	n = 0;
	while (n < nbr_pipes)
	{
		if (pipe(shell->fd[n]) == -1)
			return (print_error(errno, NULL, PRINT));
		n++;
	}
	if (pipechain_loop(table, shell))
		return (1);
	if (pipe_parent(shell, table, nbr_pipes))
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
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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
	reset_redirections(row);
	return (0);
}

/*-------------------------------------------------------------
Main function for executor
signal() ignores the handle_signals().
This is needed to catch the exit code of such programs like cat and sleep.
and also for ./minishell in minishell
---------------------------------------------------------------*/
int	executor(char **envp, t_list *table, t_shell *shell)
{
	t_command	*current_cmd;
	int			nbr_pipes;

	shell->pid = NULL;
	shell->fd = NULL;
	if (shell->syntax_error == true)
		return (1);
	if (handle_heredoc(table, envp))
		return (2);
	signal(SIGINT, SIG_IGN);
	nbr_pipes = ft_lstsize(table) - 1;
	if (nbr_pipes == 0)
	{
		current_cmd = (t_command *) table->content;
		set_original_std(current_cmd);
		if (execute_single_command(envp, current_cmd, shell))
			return (reset_redirections(current_cmd), 3);
	}
	else if (nbr_pipes > 0)
	{
		if (execute_pipechain(table, nbr_pipes, shell))
			return (free_fd_pid(shell, nbr_pipes), 4);
		free_fd_pid(shell, nbr_pipes);
	}
	return (0);
}
