/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fd_pid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:13:49 by maustel           #+#    #+#             */
/*   Updated: 2024/11/27 16:14:46 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_double_int(int **to_free, int nbr_pipes)
{
	int	i;

	i = 0;
	while (i < nbr_pipes)
	{
		free (to_free[i]);
		to_free[i] = NULL;
		i++;
	}
	if (to_free)
		free (to_free);
	to_free = NULL;
}

void	free_fd_pid(t_shell *shell, int nbr_pipes)
{
	if (shell->pid)
	{
		free (shell->pid);
		shell->pid = NULL;
	}
	if (shell->fd)
		free_double_int(shell->fd, nbr_pipes);
}

/*-------------------------------------------------------------
init and allocate memory for **fd and *pid
---------------------------------------------------------------*/
int	init_fd_pid(t_shell *shell, int nbr_pipes)
{
	int	i;

	shell->pid = NULL;
	shell->pid = malloc(sizeof(pid_t) * nbr_pipes + 1);
	if (!shell->pid)
		return (1);
	shell->fd = NULL;
	shell->fd = malloc(sizeof(int *) * nbr_pipes);
	if (!shell->fd)
		return (2);
	i = 0;
	while (i < nbr_pipes)
	{
		shell->fd[i] = NULL;
		shell->fd[i] = malloc(sizeof(int) * 2);
		if (!shell->fd[i])
			return (3);
		shell->fd[i][0] = 0;
		shell->fd[i][1] = 0;
		i++;
	}
	return (0);
}
