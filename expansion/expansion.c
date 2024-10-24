/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:41:21 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/21 16:29:22 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell_eichhoernchen.h"


void expansion(t_shell *shell, char **env)
{
	if (iterate_table(shell->table, env) == -1)
		return ;
	if (remove_quotes(shell->table) == -1)
		return ;
}

// need to handle exit_code stuff like aaa$? and aaa$?aaaa
// need to get the exit_code in double quotes

