/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:16:35 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/14 15:47:47 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

bool	is_numeric(char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

void	ft_exit(t_command *row)
{
	int exit_status;

	exit_status = print_error(0, NULL, NOTPRINT);
	if (row->args[1])
	{
		if (is_numeric(row->args[1]))
			exit_status = print_error(ft_atoi(row->args[1]) % 256, NULL, NOTPRINT);
		else
			exit_status = print_error(E_NUMERICARG, row->args[1], PRINT);
		if (row->args[2])
			exit_status = print_error(E_TOOMANYARG, NULL, PRINT);
	}
	// ft_printf("Exiting with status %d\n", exit_status);
	exit(exit_status);
}




