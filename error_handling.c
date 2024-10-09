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

#include "executor.h"

int	custom_error(int err_no, char *str)
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
	return (err_no);
}

int	print_error(int err_no, char *str, t_exec *test)
{
	if (str)
	{
		ft_putstr_fd(str, 2);
		write(2, ": ", 2);
	}
	if (err_no > 106)
		test->exit_code = custom_error(err_no, str);
	else
	{
		perror(NULL);
		test->exit_code = err_no;
	}
	return (err_no);
}
