/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:41:26 by maustel           #+#    #+#             */
/*   Updated: 2024/10/21 14:54:50 by maustel          ###   ########.fr       */
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
---------------------------------------------------------------*/
char	*get_check_path(char *cmd, char **envp, t_exec *test)
{
	char	*path;

	path = get_path(cmd, envp);
	if (!path)
	{
		print_error(E_PATH, NULL, test);
		return (NULL);
	}
	else if (access(path, F_OK) != 0)
	{
		if (path)
			free (path);
		if (cmd_is_path(cmd))
			print_error(E_FILENOEXIST, cmd, test);
		else
			print_error(127, cmd, test);
		return (NULL);
	}
	if (access(path, X_OK) != 0)
	{
		if (path)
			free (path);
		print_error(E_NOPERMISSION, cmd, test);
		return (NULL);
	}
	return (path);
}

/*-------------------------------------------------------------
Handle everything we need to handle before execve
---------------------------------------------------------------*/
int	handle_stuff(char **envp, t_command *example, t_exec *test)
{
	// if (is_built_in)
	// 	ecexute_builtin();
	if (handle_heredoc(*example, test))
		return (1);
	if (check_files(*example, test))
		return (2);
	if (exec_redirections(*example, test))
		return (3);
	example->path = get_check_path(example->args[0], envp, test);
	if (!example->path)
		return (3);
	return (0);
}
