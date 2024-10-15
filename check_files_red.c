/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files_red.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:07:26 by maustel           #+#    #+#             */
/*   Updated: 2024/10/15 12:44:41 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	create_file(char *filename, t_exec *test)
{
	int	fd;

	fd = 0;
	if (ft_strlen(filename) == 0)
		print_error(EPERM, filename, test);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		print_error(errno, NULL, test);
	if (close(fd) == -1)
		print_error(errno, NULL, test);
}

int	check_input_files(t_command example, t_exec *test, int i)
{

	if (access(example.filename[i], F_OK) == -1)
		return (print_error(EPERM, example.filename[i], test));
	else if (access(example.filename[i], R_OK) == -1)
		return (print_error(EPERM, example.filename[i], test));
	else
	{
		test->final_infile = example.filename[i];
		test->final_in_red = example.red_symbol[i];
	}
	return (0);
}

// int	open_output_files(t_command example, t_exec *test)
// {
// 	int	i;
// 	int	fd;

// 	fd = 0;
// 	i = 0;
// 	while (example.filename[i])
// 	{
// 		if (example.red_symbol[i] && (example.red_symbol[i][0] == '>'))
// 		{
// 			if (access(example.filename[i], F_OK) == -1)
// 				create_file(fd, example.filename[i], test);
// 			else if (access(example.filename[i], R_OK) == -1)
// 				return (print_error(EPERM, example.filename[i], test));
// 			test->final_outfile = example.filename[i];
// 			test->final_out_red = example.red_symbol[i];
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int	check_output_files(t_command example, t_exec *test, int i)
{
	if (access(example.filename[i], F_OK) == -1)
		create_file(example.filename[i], test);
	if (access(example.filename[i], W_OK) == -1)
		return (print_error(E_NOPERMISSION, example.filename[i], test));
	test->final_outfile = example.filename[i];
	test->final_out_red = example.red_symbol[i];
	return (0);
}

int	check_redirections(t_command example, t_exec *test)
{
	int	i;

	test->final_infile = NULL;
	test->final_outfile = NULL;
	test->final_in_red = NULL;
	test->final_out_red = NULL;
	if (example.filename && example.red_symbol)
	{
		i = 0;
		while (example.filename[i])
		{
			if (example.red_symbol[i] && (example.red_symbol[i][0] == '>'))
			{
				if (check_output_files(example, test, i))
					return (1);
			}
			else if (example.red_symbol[i] && (example.red_symbol[i][0] == '<'))
			{
				if (check_input_files(example, test, i))
					return (2);
			}
			i++;
		}
		if (handle_redirections(example, test))
			return (3);
	}
	return (0);
}
