/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:01:02 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/19 12:11:48 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parser(t_shell *shell)
{
	t_list		*tmp;
	t_list		*new_node;
	t_command	*new_cmd;

	tmp = NULL;
	new_node = NULL;
	new_cmd = NULL;
	if (shell->syntax_error == true)
		return ;
	shell->table = NULL;
	if (create_table(shell, new_node, new_cmd, tmp) == -1)
		return ;
	if (!shell->table)
		return ;
}
