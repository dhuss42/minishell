/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:41:26 by maustel           #+#    #+#             */
/*   Updated: 2024/11/27 11:24:38 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
F_OK tests for the existence of the file
X_OK tests whether the file exists and grants execute permissions
if its directory, it prints command not found: (not necessary,
will be treated in exec child)
// if (S_ISDIR(filestat.st_mode))
	// 	return (print_error(127, row->args[0], PRINT));
---------------------------------------------------------------*/
int	get_check_path(t_command *row, char **envp)
{
	struct stat	filestat;

	if (!row->args[0])
		return (0);
	ft_memset(&filestat, 0, sizeof(filestat));
	stat(row->args[0], &filestat);
	if (row->args[0][0] == '.' && (row->args[0][1] == '/'
		|| (row->args[0][1] == '.' && row->args[0][2] == '/')))
	{
		if (S_ISDIR(filestat.st_mode))
			return (print_error(E_ISDIRECTORY, row->args[0], PRINT));
	}
	row->path = get_path(row->args[0], envp);
	if (!row->path)
		return (print_error(E_PATH, NULL, PRINT));
	if (access(row->path, F_OK) != 0)
	{
		if (cmd_is_path(row->args[0]))
			return (print_error(E_FILENOEXIST, row->args[0], PRINT));
		else
			return (print_error(127, row->args[0], PRINT));
	}
	else if (access(row->path, X_OK) != 0)
		return (print_error(E_NOPERMISSION_PATH, row->args[0], PRINT));
	return (0);
}
