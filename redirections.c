/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:38:08 by maustel           #+#    #+#             */
/*   Updated: 2024/10/22 12:01:00 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/*-------------------------------------------------------------
duplicate fd from final infile to stdin
---------------------------------------------------------------*/
int	redirect_input(t_command row,t_exec *test)
{
	int	fd;

	fd = 0;
	// if (row.final_in_red[1] == '\0')
	fd = open(row.final_infile, O_RDONLY);
	// else if (row.final_in_red[1] == '<')
	// 	fd = open("tmp/heredoc_temp", O_RDONLY);
	if (dup2(fd, 0) == -1)
		return (print_error(errno, NULL, test));
	if (close(fd) == -1)
		return (print_error(errno, NULL, test));
	return (0);
}

/*-------------------------------------------------------------
duplicate fd from final outfile to stdout
---------------------------------------------------------------*/
int	redirect_output(t_command row, t_exec *test)
{
	int	fd;

	fd = 0;
	if (row.final_out_red[1] == '\0')
		fd = open(row.final_outfile, O_WRONLY | O_TRUNC);
	else if (row.final_out_red[1] == '>')
		fd = open(row.final_outfile, O_WRONLY | O_APPEND);
	else
		return (1);
	if (fd == -1)
		return (print_error(errno, NULL, test));
	if (dup2(fd, 1) == -1)
		return (print_error(errno, NULL, test));
	if (close(fd) == -1)
		return (print_error(errno, NULL, test));
	return (0);
}

/*-------------------------------------------------------------
Execute redirections for each row in table
---------------------------------------------------------------*/
int	exec_redirections(t_list *table, t_exec *test)
{
	t_command	*row;
	t_list		*tmp;

	tmp = table;
	while (tmp)
	{
		row = (t_command *)table->content;
		if (row->final_outfile && row->final_out_red)
		{
			if (redirect_output(*row, test))
				return (1);
		}
		if (row->final_infile && row->final_in_red)
		{
			if (redirect_input(*row, test))
				return (2);
		}
		tmp = tmp->next;
	}
	return (0);
	// row = (t_command *)table->content;
	// if (row->final_outfile && row->final_out_red)
	// {
	// 	if (redirect_output(*row, test))
	// 		return (1);
	// }
	// if (row->final_infile && row->final_in_red)
	// {
	// 	if (redirect_input(*row, test))
	// 		return (2);
	// }
}
