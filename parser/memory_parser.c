/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:21:11 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/29 11:09:58 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_eichhoernchen.h"

void	free_table_parser(t_shell *parsing)
{
	t_list	*tmp;
	t_list	*next;
	t_command *cmd;

	tmp = parsing->table;
	while (tmp != NULL)
	{
		cmd = (t_command*)tmp->content;
		if (cmd)
		{
			if (cmd->args)
				clear_all(cmd->args);
			if (cmd->filename)
				clear_all(cmd->filename);
			if (cmd->red_symbol)
				clear_all(cmd->red_symbol);
			free(cmd);
		}
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	parsing->table = NULL;
}
