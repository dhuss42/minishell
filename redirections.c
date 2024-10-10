/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:38:08 by maustel           #+#    #+#             */
/*   Updated: 2024/10/10 16:34:29 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	handle_redirections(t_command example, t_exec *test)
{
	int	fd;

	if (test->final_outfile && test->final_out_red)
	{
		if (test->final_out_red[1] != '>')
			fd = open(test->final_outfile, O_WRONLY | O_TRUNC);
		// else if (test->final_out_red[1] == '>')
		// 	fd = open(test->final_outfile, O_WRONLY | O_APPEND);
		else
			return (1);
		if (fd == -1)
			return (print_error(errno, NULL, test));
		if (dup2(fd, 1) == -1)
			return (print_error(errno, NULL, test));
		if (close(fd) == -1)
			return (print_error(errno, NULL, test));

	}
	if (test->final_infile && test->final_in_red)
	{
		if (test->final_in_red[1] != '<')
		{
			fd = open(test->final_infile, O_RDONLY);
			if (dup2(fd, 0) == -1)
				return (print_error(errno, NULL, test));
			if (close(fd) == -1)
				return (print_error(errno, NULL, test));
		}
	}
	return (0);
}
