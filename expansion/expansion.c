/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:41:21 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/27 12:50:06 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expansion(t_shell *shell, char **env)
{
	if (shell->syntax_error == true)
		return ;
	if (iterate_table(shell->table, env) == -1)
		return ;
	if (remove_quotes(shell->table, shell) == -1)
		return ;
	if (shell->syntax_error == false)
		print_error(0, NULL, NOTPRINT);
}

// split check_for_expansion