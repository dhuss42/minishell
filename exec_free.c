/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:50:18 by maustel           #+#    #+#             */
/*   Updated: 2024/10/21 14:56:00 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/*-------------------------------------------------------------

---------------------------------------------------------------*/
void	free_double(char **to_free)
{
	int	i;

	i = 0;
	while (to_free[i])
	{
		free (to_free[i]);
		to_free[i] = NULL;
		i++;
	}
	if (to_free)
		free (to_free);
	to_free = NULL;
}

/*-------------------------------------------------------------

---------------------------------------------------------------*/
void	free_paths(char **split_paths, char **append)
{
	if (split_paths)
		free_double (split_paths);
	if (append)
		free_double(append);
}

// void	free_exec(t_exec *exec)
// {
// 	if (exec->heredoc_del)
// 		free_double(exec);
// }

/*-------------------------------------------------------------

---------------------------------------------------------------*/
int	free_row(t_command *cmd)	//usefull for whole project
{
	if (cmd->args)
		free_double(cmd->args);
	if (cmd->filename)
		free_double(cmd->filename);
	if (cmd->red_symbol)
		free_double(cmd->red_symbol);
	if (cmd->path)
	{
		free (cmd->path);
		cmd->path = NULL;
	}
	if (cmd)
		free (cmd);
	cmd = NULL;
	return (1);
}

int	free_table(t_list *table)
{
	t_list	*tmp;
	t_list	*next;
	t_command *cmd;

	tmp = table;
	while (tmp != NULL)
	{
		cmd = (t_command*)tmp->content;
		if (cmd)
			free_row(cmd);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	// if (table->exec)
	// 	free_exec(exec);
	table = NULL;
	return (1);
}
