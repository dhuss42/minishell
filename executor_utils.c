/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:41:26 by maustel           #+#    #+#             */
/*   Updated: 2024/10/25 09:36:38 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/*-------------------------------------------------------------
check if command is a path f.e.: /bin/ls
---------------------------------------------------------------*/
bool	cmd_is_path(char *cmd)
{
	if (ft_strchr(cmd, '/') != NULL)
		return (true);
	else
		return (false);
}

/*-------------------------------------------------------------
Check if path / command is valid before writing it to path
for each row in table
---------------------------------------------------------------*/
int	get_check_path(t_list *table, char **envp)
{
	t_list		*tmp;
	t_command	*row;

	tmp = table;
	while (tmp)
	{
		row = (t_command *)tmp->content;
		row->path = get_path(row->args[0], envp);
		if (!row->path)
			return (print_error(E_PATH, NULL, PRINT));
		else if (access(row->path, F_OK) != 0)
		{
			if (cmd_is_path(row->args[0]))
				return (print_error(E_FILENOEXIST, row->args[0], PRINT));
			else
				return (print_error(127, row->args[0], PRINT));
		}
		else if (access(row->path, X_OK) != 0)
			return (print_error(E_NOPERMISSION, row->args[0], PRINT));
		tmp = tmp->next;
	}
	return (0);
}

/*-------------------------------------------------------------
Handle everything we need to handle before execve
---------------------------------------------------------------*/
int	handle_stuff(char **envp, t_list *table)
{
	// if (is_built_in)
	// 	ecexute_builtin();
	if (handle_heredoc(table))
		return (1);
	if (check_files(table))
		return (2);
	if (get_check_path(table, envp))
		return (3);
	return (0);
}
