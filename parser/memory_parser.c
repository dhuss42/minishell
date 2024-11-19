/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:21:11 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/19 12:11:44 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_command(t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->args)
		clear_all(cmd->args);
	if (cmd->filename)
		clear_all(cmd->filename);
	if (cmd->red_symbol)
		clear_all(cmd->red_symbol);
	free(cmd);
}

void	free_table_parser(t_shell *parsing)
{
	t_list	*tmp;
	t_list	*next;

	tmp = parsing->table;
	while (tmp != NULL)
	{
		next = tmp->next;
		free_command((t_command *)tmp->content);
		free(tmp);
		tmp = next;
	}
	parsing->table = NULL;
}

void	memory_parser(t_shell *parsing, t_command *cmd)
{
	free_command(cmd);
	free_table_parser(parsing);
}
