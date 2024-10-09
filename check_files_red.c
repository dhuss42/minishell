/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files_red.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:07:26 by maustel           #+#    #+#             */
/*   Updated: 2024/10/09 12:14:04 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	check_input_files(t_command example, t_exec *test)
{
	int	i;

	i = 0;
	while (example.filename[i])
	{
		if (example.red_symbol[i] && example.red_symbol)
		{
			if (access(example.filename[i], F_OK) == -1)
				return (print_error(E_FILENOTEXIST, example.filename[i], test));
			if (access(example.filename[i], R_OK) == -1)
				return (print_error(E_NOPERMIT, example.filename[i], test));
			else
			{
				test->final_infile = example.filename[i];
				test->final_in_red = example.red_symbol[i];
			}
		}
		i++;
	}
	return (0);
}

int	handle_redirections(t_command example, t_exec *test)
{
	test->final_infile = NULL;
	test->final_outfile = NULL;
	test->final_in_red = NULL;
	test->final_out_red = NULL;

	if (check_input_files(example, test))
		return (1);
	// check_input_files(example);
	// check_output_files(example);
	return (0);
}