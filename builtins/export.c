/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:06:50 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/19 12:34:23 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_export(t_shell *shell, t_command *row)
{
	shell->i++;
	if (row->args[shell->i] == NULL)
	{
		if (export_no_argument(shell) == -1)
			return (-1);
		else
			return (0);
	}
	else
	{
		if (export_with_args(shell, row) == -1)
			return (-1);
		else
			return (0);
	}
}

// gets length of the new double char array
// that will hold all the keys=variables
// allocates that double char array (tmp)
// checks if the keys typed by User exist and replaces them in the og envs
// copies these envs into tmp & appends the user's input if its valid
// frees original envs
// copies tmp into envs
