/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:16:35 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/18 11:32:17 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

bool	is_numeric(char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '+' || str[i] == '-')
			i++;
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	ft_exit(t_shell *shell, t_command *row)
{
	int	exit_code;

	shell->exit = true;
	if (row->args[1])
	{
		if (is_numeric(row->args[1]))
		{
			exit_code = ft_atoi(row->args[1]) % 256;
			if (exit_code < 0)
				exit_code += 256;
			print_error(exit_code, NULL, NOTPRINT);
		}
		else
			print_error(E_NUMERICARG, row->args[1], PRINT);
		if (row->args[2])
		{
			print_error(E_TOOMANYARG, NULL, PRINT);
			shell->exit = false;
		}
	}
	// ft_printf("Exiting with status %d\n", print_error(-1, NULL, NOTPRINT));

	return (0);
}




