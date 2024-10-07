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
	return (err_no);
}

int	print_error(int err_no, char *str)
{
	if (str)
	{
		ft_putstr_fd(str, 2);
		write(2, ": ", 2);
	}
	if (err_no > 106)
		custom_error(err_no, str);
	else
		perror(NULL);
	return (err_no);
}
