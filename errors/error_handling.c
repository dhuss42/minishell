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

#include "../minishell.h"

/*-------------------------------------------------------------
Print custom errors 1
---------------------------------------------------------------*/
static int	custom_error_print_1(int err_no)
{
	if (err_no == E_PATH)
		ft_putstr_fd("function get_path failed\n", 2);
	else if (err_no == E_FILENOEXIST)
	{
		ft_putstr_fd("no such file or directory\n", 2);
		return (127);
	}
	else if (err_no == E_DIRNOEXIST)
	{
		ft_putstr_fd("no such file or directory\n", 2);
		return (1);
	}
	else if (err_no == E_NOPERMISSION_PATH)
	{
		ft_putstr_fd("Permission denied\n", 2);
		return (126);
	}
	else if (err_no == E_NOPERMISSION_FILE)
	{
		ft_putstr_fd("Permission denied\n", 2);
		return (1);
	}
	return (err_no);
}

static int	custom_error_message_2(int err_no, char *str)
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
	return (err_no);
}

static int	custom_error_message_1(int err_no, char *str)
{
	if (err_no == E_NOTSET)
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
	return (err_no);
}

static int	custom_err(int err_no, char *str)
{
	if (str && (err_no == E_NOTSET || err_no == E_CDNOSUCHFOD
			|| err_no == E_NOTVALIDIDENT))
		return (custom_error_message_1(err_no, str));
	else if (str && (err_no == E_NUMERICARG || err_no == E_SYNTAXERROR))
		return (custom_error_message_2(err_no, str));
	else if (err_no <= E_INIT_TERMINAL)
		return (custom_error_print_1(err_no));
	else if (err_no > E_INIT_TERMINAL)
		return (custom_error_print_2(err_no));
	return (err_no);
}

/*-------------------------------------------------------------
print error message and update static int exit_code
---------------------------------------------------------------*/
int	print_error(int err_no, char *str, int print)
{
	static int	exit_code = 0;

	if (print == NOTPRINT && err_no >= 0)
		exit_code = err_no;
	else if (print == PRINT && err_no > 0)
	{
		ft_putstr_fd("minishell: ", 2);
		if (str && err_no != E_NUMERICARG && err_no != E_SYNTAXERROR
			&& err_no != E_NOTSET && err_no != E_CDNOSUCHFOD
			&& err_no != E_NOTVALIDIDENT)
		{
			ft_putstr_fd(str, 2);
			write(2, ": ", 2);
		}
		if (err_no > 106)
			exit_code = custom_err(err_no, str);
		else
		{
			perror(NULL);
			exit_code = err_no;
		}
	}
	return (exit_code);
}
