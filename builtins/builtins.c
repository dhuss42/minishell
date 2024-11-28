/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:07:24 by maustel           #+#    #+#             */
/*   Updated: 2024/11/28 17:03:57 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*-------------------------------------------------------------
Check if command is builtin with more than 3 characters
---------------------------------------------------------------*/
static int	builtins_2(t_shell *shell, t_command *row)
{
	if (ft_strlen(row->args[0]) == 4)
	{
		if (ft_strncmp(row->args[0], "exit", 4) == 0)
			return (ft_exit(shell, row));
	}
	else if (ft_strlen(row->args[0]) == 5)
	{
		if (ft_strncmp(row->args[0], "unset", 5) == 0)
			return (ft_unset(shell, row));
	}
	else if (ft_strlen(row->args[0]) == 6)
	{
		if (ft_strncmp(row->args[0], "export", 6) == 0)
			return (ft_export(shell, row));
	}
	if (ft_strncmp(row->args[0], "echo", 4) == 0)
		return (ft_echo(shell, row));
	return (1);
}

/*-------------------------------------------------------------
Check if command is builtin with less than 4 characters
---------------------------------------------------------------*/
static int	builtins_1(t_shell *shell, t_command *row)
{
	if (shell->table == NULL)
		return (-1);
	if (row->args[0] == NULL)
		return (1);
	if (ft_strlen(row->args[0]) == 2)
	{
		if (ft_strncmp(row->args[0], "cd", 2) == 0)
			return (ft_cd(shell, row));
	}
	else if (ft_strlen(row->args[0]) == 3)
	{
		if (ft_strncmp(row->args[0], "pwd", 3) == 0)
			return (ft_pwd());
		else if (ft_strncmp(row->args[0], "env", 3) == 0)
			return (ft_env(shell));
	}
	return (1);
}

/*-------------------------------------------------------------
Redirect to normal stdin / stdout (necessary for single command,
because builtins are called in main process, not in child)
---------------------------------------------------------------*/
static void	re_redirect(t_command *row)
{
	dup2(row->original_stdout, STDOUT_FILENO);
	dup2(row->original_stdin, STDIN_FILENO);
	dup2(row->original_stderr, STDERR_FILENO);
}

/*-------------------------------------------------------------
Check if command is builtin and call function, if it is.
---------------------------------------------------------------*/
int	check_builtins(t_shell *shell, t_command *row)
{
	int	is_builtin;

	shell->i = 0;
	is_builtin = 0;
	if (row->args[0])
	{
		if (ft_strlen(row->args[0]) < 4)
			is_builtin = builtins_1(shell, row);
		else if (ft_strlen(row->args[0]) >= 4)
			is_builtin = builtins_2(shell, row);
		if (is_builtin == 0)
		{
			re_redirect(row);
			return (0);
		}
		else if (is_builtin < 0)
		{
			re_redirect(row);
			return (-1);
		}
	}
	return (1);
}
