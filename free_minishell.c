/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:55:34 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/27 11:10:59 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_minishell(t_shell *shell, char *input)
{
	free(input);
	ft_lstclear(&shell->list, free_token);
	if (shell->syntax_error == false)
		free_table(shell->table);
	if (shell->exit == true)
		clear_all(shell->env);
}