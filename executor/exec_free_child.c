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

#include "../executor.h"

void	free_child_exit(t_shell *shell, int exit_code)
{
	if (exit_code == 0)
		print_error(0, NULL, NOTPRINT);
	ft_lstclear(&shell->list, free_token);
	free_table(shell->table);
	exit (exit_code);
}
