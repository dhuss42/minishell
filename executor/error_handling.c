/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:13:03 by maustel           #+#    #+#             */
/*   Updated: 2024/10/07 13:13:03 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/*-------------------------------------------------------------
Print custom errors
---------------------------------------------------------------*/
int	custom_error(int err_no)
{
	if (err_no == E_PATH)
		ft_putstr_fd("function get_path failed\n", 2);
	else if (err_no == 127)
		ft_putstr_fd("command not found\n", 2);
	// else if (err_no == E_PARENT)
	// 	ft_putstr_fd("error in parent_function\n", 2);
	else if (err_no == E_INIT_TERMINAL)
		ft_putstr_fd("error in init_terminal\n", 2);
	else if (err_no == E_BUILTIN)
		ft_putstr_fd("error in builtins\n", 2);
	else if(err_no == E_FILENOEXIST)
	{
		ft_putstr_fd("no such file or directory\n", 2);
		return (127);
	}
	else if(err_no == E_NOPERMISSION)
	{
		ft_putstr_fd("Permission denied\n", 2);
		return (126);
	}
	else if(err_no == E_FILE_ISDIRECTORY)
	{
		ft_putstr_fd("is a directory\n", 2);
		return (1);
	}
	else if(err_no == E_CMD_ISDIRECTORY)
	{
		ft_putstr_fd("is a directory\n", 2);
		return (126);
	}
	else if (err_no == E_TOOMANYARG)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	return (err_no);
}

int	custom_error_message(int err_no, char *str)
{
	if (err_no == E_NUMERICARG)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	else if (err_no == E_SYNTAXERROR)
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\'\n", 2);
		err_no = 2;
	}
	else if (err_no == E_NOTSET)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" not set\n", 2);
		err_no = 1;
	}
	else if (err_no == E_CDNOSUCHFOD)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" No such file or directory\n", 2);
		err_no = 1;
	}
	else if (err_no == E_NOTVALIDIDENT)
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\': not a valid identifier\n", 2);
		err_no = 1;
	}
	// printf("setting err_no = %d\n", err_no);
	return (err_no);
}

/*-------------------------------------------------------------
print error message and update static int exit_code
---------------------------------------------------------------*/
int	print_error(int err_no, char *str, int print)
{
	static int	exit_code = 0;

	// printf(RED"in print_error\n"WHITE);
	if (print == NOTPRINT && err_no >= 0)
		exit_code = err_no;
	else if (print == PRINT && err_no > 0)
	{
		ft_putstr_fd("minishell: ", 2);
		if (str && err_no != E_NUMERICARG && err_no != E_SYNTAXERROR && err_no != E_NOTSET && err_no != E_CDNOSUCHFOD && err_no != E_NOTVALIDIDENT) // etwas unschön gelöst von mir
		{
			ft_putstr_fd(str, 2);
			write(2, ": ", 2);
		}
		if (err_no > 106)
		{
			if (str && (err_no == E_NUMERICARG || err_no == E_SYNTAXERROR || err_no == E_NOTSET || err_no == E_CDNOSUCHFOD || err_no == E_NOTVALIDIDENT))
			{
				// printf("going int custom_error_message\n");
				// printf("str: %s\n", str);
				exit_code = custom_error_message(err_no, str);
				// printf("exit code after custom error message = %d\n", exit_code);
			}
			else
			{
				// printf("going int custom_error\n");
				exit_code = custom_error(err_no);
				// printf("exit code after custom error = %d\n", exit_code);
			}
		}
		else
		{
			perror(NULL);
			exit_code = err_no;
		}
	}
	// printf("exit_code is: %d\n", exit_code);
	return (exit_code);
}


