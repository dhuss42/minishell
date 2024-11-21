/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:26:24 by maustel           #+#    #+#             */
/*   Updated: 2024/11/21 11:26:24 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*-------------------------------------------------------------
Print custom errors 2
---------------------------------------------------------------*/
int	custom_error_print_2(int err_no)
{
	if (err_no == E_INIT_TERMINAL)
		ft_putstr_fd("error in init_terminal\n", 2);
	else if (err_no == E_BUILTIN)
		ft_putstr_fd("error in builtins\n", 2);
	else if(err_no == E_FILE_ISDIRECTORY)
	{
		ft_putstr_fd("is a directory\n", 2);
		return (1);
	}
	else if (err_no == E_TOOMANYARG)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	else if (err_no == 127)
		ft_putstr_fd("command not found\n", 2);
	return (err_no);
}
