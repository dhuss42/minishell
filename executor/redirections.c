/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:38:08 by maustel           #+#    #+#             */
/*   Updated: 2024/10/29 11:45:03 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/*-------------------------------------------------------------
duplicate fd from final infile to stdin
---------------------------------------------------------------*/
int	redirect_input(t_command row, int *fd)
{
	*fd = open(row.final_infile, O_RDONLY);
	if (dup2(*fd, 0) == -1)
		return (print_error(errno, NULL, PRINT));
	if (close(*fd) == -1)
		return (print_error(errno, NULL, PRINT));
	return (0);
}

/*-------------------------------------------------------------
duplicate fd from final outfile to stdout
---------------------------------------------------------------*/
int	redirect_output(t_command row, int *fd)
{
	if (row.final_out_red[1] == '\0')
		*fd = open(row.final_outfile, O_WRONLY | O_TRUNC);
	else if (row.final_out_red[1] == '>')
		*fd = open(row.final_outfile, O_WRONLY | O_APPEND);
	else
		return (1);
	if (*fd == -1)
		return (print_error(errno, NULL, PRINT));
	if (dup2(*fd, 1) == -1)
		return (print_error(errno, NULL, PRINT));
	if (close(*fd) == -1)
		return (print_error(errno, NULL, PRINT));
	return (0);
}

/*-------------------------------------------------------------
Execute redirections for single command
---------------------------------------------------------------*/
int	exec_redirections(t_command *row)
{
	int	fd;

	if (row->final_outfile && row->final_out_red)
	{
		if (redirect_output(*row, &fd))
			return (1);
	}
	if (row->final_infile && row->final_in_red)
	{
		if (redirect_input(*row, &fd))
			return (2);
	}
	return (0);
}
