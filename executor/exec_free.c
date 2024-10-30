/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:50:18 by maustel           #+#    #+#             */
/*   Updated: 2024/10/30 15:44:41 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/*-------------------------------------------------------------
free double-pointer
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
Used in find_path
---------------------------------------------------------------*/
void	free_paths(char **split_paths, char **append)
{
	if (split_paths)
		free_double (split_paths);
	if (append)
		free_double(append);
}

/*-------------------------------------------------------------
delete all temporary heredoc files
---------------------------------------------------------------*/
void	delete_heredoc_files(char *path)
{
	if (access(path, F_OK) == 0)
		unlink(path);
}

/*-------------------------------------------------------------
free all pointers of a row
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
	if (cmd->heredoc_file_path)
	{
		delete_heredoc_files(cmd->heredoc_file_path);
		free (cmd->heredoc_file_path);
		cmd->heredoc_file_path = NULL;
	}
	if (cmd)
		free (cmd);
	cmd = NULL;
	return (1);
}

/*-------------------------------------------------------------
Free and set to NULL all pointers of whole table
---------------------------------------------------------------*/
int	free_table(t_list *table)
{
	t_list	*tmp;
	t_list	*del;
	t_command *cmd;

	tmp = table;
	while (tmp != NULL)
	{
		cmd = (t_command*)tmp->content;
		// printf("ID: %d\n", cmd->id);
		if (cmd)
			free_row(cmd);
		del = tmp;
		tmp = tmp->next;
		free(del);
	}
	table = NULL;
	return (1);
}
