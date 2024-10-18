/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:41:26 by maustel           #+#    #+#             */
/*   Updated: 2024/10/18 13:42:18 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

bool	cmd_is_path(char *cmd)
{
	if (ft_strchr(cmd, '/') != NULL)
		return (true);
	else
		return (false);
}

/*	when binary file not exists ./"filename"--> "No such file or directory", Errorcode: 127
	when no permission for binary file--> "Permission denied", Errorcode: 126
	when command does not exist-->"command not found", errorcode: 127
*/
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

int	handle_stuff(char **envp, t_command *example, t_exec *test)
{
	// if (is_built_in)
	// 	ecexute_builtin();
	// handle heredoc
	if (check_files(*example, test))
		return (1);
	if (exec_redirections(*example, test))
		return (2);
	example->path = get_check_path(example->args[0], envp, test);
	if (!example->path)
		return (3);
	return (0);
}
