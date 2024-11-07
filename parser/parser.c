/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:01:02 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/18 16:23:16 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_eichhoernchen.h"

void	parser(t_shell *shell)
{
	if (shell->syntax_error == true)
		return ;
	shell->table = NULL;
	if (create_table(shell) == -1)
	{
		return ;
	}
	if (!shell->table)
	{
		return ;
	}
}

// need to go through the parser to check if all frees were handled properly