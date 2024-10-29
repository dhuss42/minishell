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
	else if (err_no == E_PARENT)
		ft_putstr_fd("error in parent_function\n", 2);
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
	else if(err_no == E_ISDIRECTORY)
	{
		ft_putstr_fd("Is a directory\n", 2);
		err_no = 1;
	}
	else if (err_no == E_SYNTAXERROR)
		ft_putstr_fd("syntax error near unexpected token\n", 2);
	return (err_no);
}

/*-------------------------------------------------------------
if binary from command failed, for example for "Is a directory"
or grep o doesnt find lines with o
--> how to stop printing "No such file or directory"?!
---------------------------------------------------------------*/
int	print_error(int err_no, char *str, int print)
{
	static int	exit_code = 0;

	if (print == NOTPRINT && err_no >= 0)
		exit_code = err_no;
	else if (print == PRINT && err_no > 0)
	{
		ft_putstr_fd("minishell: ", 2);
		if (str)
		{
			ft_putstr_fd(str, 2);
			write(2, ": ", 2);
		}
		if (err_no > 106)
			exit_code = custom_error(err_no);
		else
		{
			perror(NULL);
			exit_code = err_no;
		}
	}
	return (exit_code);
}

// int main()
// {
// 	print_error(E_FILENOEXIST, "test", PRINT);
// 	print_error(5, NULL, NOTPRINT);
// 	printf("Exit-code:%d\n", print_error(0, NULL, NOTPRINT));
// 	return (0);
// }
