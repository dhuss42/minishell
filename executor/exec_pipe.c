/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:39:05 by maustel           #+#    #+#             */
/*   Updated: 2024/12/01 13:04:49 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*-------------------------------------------------------------
Close all opened filedescriptors from piping, we won't need
---------------------------------------------------------------*/
static int	close_fds(t_shell *shell, int id, int nbr_pipes)
{
	int	i;

	i = 0;
	while (i < nbr_pipes)
	{
		if (id == 0 || i != id - 1)
		{
			if (close(shell->fd[i][0]) == -1)
				return (errno);
		}
		if (i != id)
		{
			if (close(shell->fd[i][1]) == -1)
				return (errno);
		}
		i++;
	}
	return (0);
}

/*-------------------------------------------------------------
Parent handler for pipechain
---------------------------------------------------------------*/
int	pipe_parent(t_shell *shell, int nbr_pipes)
{
	int		wstatus;
	int		exit_code;
	int		i;
	t_list	*tmp;

	if (close_fds(shell, -1, nbr_pipes))
		exit (print_error(errno, NULL, PRINT));
	tmp = shell->table;
	exit_code = 0;
	i = 0;
	while (i <= nbr_pipes)
	{
		if (waitpid(shell->pid[i], &wstatus, 0) == -1)
			return (1);
		if (WIFEXITED(wstatus))
			exit_code = WEXITSTATUS(wstatus);
		if (WIFSIGNALED(wstatus))
			exit_code = WTERMSIG(wstatus) + 128;
		print_error(exit_code, NULL, NOTPRINT);
		tmp = tmp->next;
		i++;
	}
	return (exit_code);
}

/*-------------------------------------------------------------
Redirect input / output for pipechild
---------------------------------------------------------------*/
static int	duplicate_fd(t_command *row, t_shell *shell, int nbr_pipes)
{
	set_original_std(row);
	if (row->id != 0 && row->final_infile == NULL)
	{
		if (dup2(shell->fd[row->id - 1][0], STDIN_FILENO) == -1)
			return (print_error(errno, NULL, PRINT));
		if (close(shell->fd[row->id - 1][0]) == -1)
			return (print_error(errno, NULL, PRINT));
	}
	if (row->final_infile)
	{
		if (redirect_input(*row, &shell->fd[row->id][0]))
			return (errno);
	}
	if (row->id != nbr_pipes && row->final_outfile == NULL)
	{
		if (redirect_output_pipe(&shell->fd[row->id][1]))
			return (errno);
	}
	if (row->final_outfile)
	{
		if (redirect_output(*row, &shell->fd[row->id][1]))
			return (errno);
	}
	return (0);
}

/*-------------------------------------------------------------
Child handler for pipechain
---------------------------------------------------------------*/
static void	pipe_child(t_command *row, t_shell *shell)
{
	int	nbr_pipes;
	int	ret;

	if (check_files(row))
		free_child_exit(shell, print_error(-1, NULL, NOTPRINT));
	nbr_pipes = ft_lstsize(shell->table) - 1;
	if (close_fds(shell, row->id, nbr_pipes))
		free_child_exit(shell, errno);
	if (duplicate_fd(row, shell, nbr_pipes))
		free_child_exit(shell, errno);
	if (check_builtins(shell, row) < 1)
		free_child_exit(shell, 0);
	ret = get_check_path(row, shell->env);
	if (ret)
		free_child_exit(shell, ret);
	if (!row->path)
		free_child_exit(shell, 0);
	if (execve(row->path, row->args, shell->env))
	{
		print_error(127, row->args[0], PRINT);
		free_child_exit(shell, 127);
	}
}

/*-------------------------------------------------------------
Loop through all the pipes
---------------------------------------------------------------*/
int	pipechain_loop(t_shell *shell)
{
	int			n;
	t_command	*row;
	t_list		*tmp;

	n = 0;
	tmp = shell->table;
	while (tmp != NULL)
	{
		row = (t_command *) tmp->content;
		shell->pid[n] = fork();
		if (shell->pid[n] == -1)
			return (print_error(errno, NULL, PRINT));
		if (shell->pid[n] == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			pipe_child(row, shell);
		}
		tmp = tmp->next;
		n++;
	}
	return (0);
}
