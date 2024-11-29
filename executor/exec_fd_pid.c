/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fd_pid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:13:49 by maustel           #+#    #+#             */
/*   Updated: 2024/11/29 12:07:21 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_fd_pid(t_shell *shell, int nbr_pipes)
{
	int	i;

	i = 0;
	if (shell->pid)
	{
		free (shell->pid);
		shell->pid = NULL;
	}
	if (shell->fd)
	{
		while (i <= nbr_pipes)
		{
			free (shell->fd[i]);
			shell->fd[i] = NULL;
			i++;
		}
		free (shell->fd);
		shell->fd = NULL;
	}
}

/*-------------------------------------------------------------
init and allocate memory for **fd and *pid
---------------------------------------------------------------*/
int	init_fd_pid(t_shell *shell, int nbr_pipes)
{
	int	i;

	shell->pid = NULL;
	shell->pid = malloc(sizeof(pid_t) * (nbr_pipes + 1));
	if (!shell->pid)
		return (1);
	shell->fd = NULL;
	shell->fd = malloc(sizeof(int *) * (nbr_pipes + 1));
	if (!shell->fd)
		return (2);
	i = 0;
	while (i <= nbr_pipes)
	{
		shell->fd[i] = NULL;
		shell->fd[i] = malloc(sizeof(int) * 2);
		if (!shell->fd[i])
			return (3);
		shell->fd[i][0] = dup(STDIN_FILENO);
		shell->fd[i][1] = dup(STDOUT_FILENO);
		shell->pid[i] = 0;
		i++;
	}
	return (0);
}
