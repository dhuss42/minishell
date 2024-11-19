/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:41:26 by maustel           #+#    #+#             */
/*   Updated: 2024/11/19 12:09:38 by dhuss            ###   ########.fr       */
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
for each row
---------------------------------------------------------------*/
int	get_check_path(t_command *row, char **envp)
{
	struct stat filestat;

	ft_memset(&filestat, 0, sizeof(filestat));
	stat(row->args[0], &filestat);
	if (S_ISDIR(filestat.st_mode))
		return (print_error(E_CMD_ISDIRECTORY, row->args[0], PRINT));
	if (!row->args[0])
		return (0);
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
		return (print_error(E_NOPERMISSION, row->args[0], PRINT));
	return (0);
}

/*-------------------------------------------------------------
Handle everything we need to handle before execve
---------------------------------------------------------------*/
int	handle_stuff(char **envp, t_command *row)
{
	if (check_files(row))
		return (1);
	if (get_check_path(row, envp))
		return (3);
	return (0);
}
