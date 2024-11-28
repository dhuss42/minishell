/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 10:50:42 by maustel           #+#    #+#             */
/*   Updated: 2024/11/15 10:50:42 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_child_exit(t_shell *shell, int exit_code)
{
	int			nbr_pipes;

	nbr_pipes = ft_lstsize(shell->table) - 1;
	free_fd_pid(shell, nbr_pipes);
	ft_lstclear(&shell->list, free_token);
	free_table(shell->table);
	exit (exit_code);
}
