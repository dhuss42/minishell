/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:38:08 by maustel           #+#    #+#             */
/*   Updated: 2024/11/27 15:58:07 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_redirections(t_command row)
{
	dup2(row.original_stdout, STDOUT_FILENO);
	dup2(row.original_stdin, STDIN_FILENO);
}

/*-------------------------------------------------------------
duplicate fd from final infile to stdin
---------------------------------------------------------------*/
int	redirect_input(t_command row, int *fd)
{
	*fd = open(row.final_infile, O_RDONLY);
	if (dup2(*fd, STDIN_FILENO) == -1)
		return (print_error(errno, NULL, PRINT));
	if (close(*fd) == -1)
		return (print_error(errno, NULL, PRINT));
	return (0);
}

/*-------------------------------------------------------------
duplicate fd from pipe outfiles to stdout and stderr
---------------------------------------------------------------*/
int	redirect_output_pipe(int *fd)
{
	if (dup2(*fd, STDOUT_FILENO) == -1)
		return (print_error(errno, NULL, PRINT));
	if (dup2(*fd, STDERR_FILENO) == -1)
		return (print_error(errno, NULL, PRINT));
	if (close(*fd) == -1)
		return (print_error(errno, NULL, PRINT));
	return (0);
}

/*-------------------------------------------------------------
duplicate fd from final outfile to stdout and stderr
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
	if (dup2(*fd, STDOUT_FILENO) == -1)
		return (print_error(errno, NULL, PRINT));
	if (dup2(*fd, STDERR_FILENO) == -1)
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

	row->original_stdout = dup(STDOUT_FILENO);
	row->original_stdin = dup(STDIN_FILENO);
	row->original_stderr = dup(STDERR_FILENO);
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
