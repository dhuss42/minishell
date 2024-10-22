/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:41:26 by maustel           #+#    #+#             */
/*   Updated: 2024/10/22 09:35:40 by maustel          ###   ########.fr       */
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
int	get_check_path(t_list *table, char **envp, t_exec *test)
{
	char	*path;
	t_list	*tmp;
	t_command	*current_row;

	tmp = table;
	while (tmp)
	{
		//...
		current_row = (t_command *)table->content;
		current_cmd->path = get_path(cmd, envp);
		if (!current_row->path)
			return (print_error(E_PATH, NULL, test));
		else if (access(current_row->path, F_OK) != 0)
		{
			if (cmd_is_path(current_row->args[0]))
				return (print_error(E_FILENOEXIST, cmd, test));
			else
				return (print_error(127, cmd, test));
		}
		else if (access(current_row->path, X_OK) != 0)
			return (print_error(E_NOPERMISSION, cmd, test));
		tmp = tmp->next;
	}
	// path = get_path(cmd, envp);
	// if (!path)
	// {
	// 	print_error(E_PATH, NULL, test);
	// 	return (NULL);
	// }
	// else if (access(path, F_OK) != 0)
	// {
	// 	if (path)
	// 		free (path);
	// 	if (cmd_is_path(cmd))
	// 		print_error(E_FILENOEXIST, cmd, test);
	// 	else
	// 		print_error(127, cmd, test);
	// 	return (NULL);
	// }
	// if (access(path, X_OK) != 0)
	// {
	// 	if (path)
	// 		free (path);
	// 	print_error(E_NOPERMISSION, cmd, test);
	// 	return (NULL);
	// }
	// return (0);
}

/*-------------------------------------------------------------
Handle everything we need to handle before execve
---------------------------------------------------------------*/
int	handle_stuff(char **envp, t_list *table, t_exec *test)
{
	// if (is_built_in)
	// 	ecexute_builtin();
	if (handle_heredoc(table, test))
		return (1);
	if (check_files(table, test))
		return (2);
	if (exec_redirections(table, test))
		return (3);
	if (get_check_path(table, envp, test))
		return (4);
	return (0);
}
