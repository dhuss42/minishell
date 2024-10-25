/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:07:26 by maustel           #+#    #+#             */
/*   Updated: 2024/10/25 15:07:30 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/*-------------------------------------------------------------
create file with read/write permission
---------------------------------------------------------------*/
int	create_file(char *filename)
{
	int	fd;

	fd = 0;
	if (ft_strlen(filename) == 0)
		return (print_error(EPERM, filename, PRINT));
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (print_error(errno, filename, PRINT));
	if (close(fd) == -1)
		return (print_error(errno, filename, PRINT));
	return (0);
}

/*-------------------------------------------------------------
check if infile exists and there is permission to read file
---------------------------------------------------------------*/
int	check_input_files(t_command *row, int i)
{
	if (row->red_symbol[i][1] == '\0')
	{
		if (access(row->filename[i], F_OK) == -1)
			return (print_error(EPERM, row->filename[i], PRINT));
		else if (access(row->filename[i], R_OK) == -1)
			return (print_error(EPERM, row->filename[i], PRINT));
		row->final_infile = row->filename[i];
	}
	else if(row->red_symbol[i][1] == '<')
		row->final_infile = row->heredoc_file_path;
	row->final_in_red = row->red_symbol[i];
	return (0);
}

/*-------------------------------------------------------------
check if outfile exists, if not create it
check if its a directory
check if there is permission to write into file
---------------------------------------------------------------*/
int	check_output_files(t_command *row, int i)
{
	struct stat filestat;

	if (access(row->filename[i], F_OK) == -1)
	{
		if (create_file(row->filename[i]))
			return (1);
	}
	stat(row->filename[i], &filestat);
	if (S_ISDIR(filestat.st_mode))
		return (print_error(E_ISDIRECTORY, row->filename[i], PRINT));
	if (access(row->filename[i], W_OK) == -1)
		return (print_error(E_NOPERMISSION, row->filename[i], PRINT));
	row->final_outfile = row->filename[i];
	row->final_out_red = row->red_symbol[i];
	return (0);
}

/*-------------------------------------------------------------
initialize final files and redirection symbols to NULL
---------------------------------------------------------------*/
void	init_final_red_files(t_command *row)
{
	row->final_infile = NULL;
	row->final_outfile = NULL;
	row->final_in_red = NULL;
	row->final_out_red = NULL;
}

/*-------------------------------------------------------------
Check all files for each row in the table
---------------------------------------------------------------*/
int	check_files(t_command *row)
{
	int			i;

	init_final_red_files(row);
	if (!row->filename || !row->red_symbol)
		return (0);
	i = 0;
	while (row->filename[i])
	{
		if (row->red_symbol[i] && row->red_symbol[i][0] == '>')
		{
			if (check_output_files(row, i))
				return (1);
		}
		else if (row->red_symbol[i] && row->red_symbol[i][0] == '<')
		{
			if (check_input_files(row, i))
				return (2);
		}
		i++;
	}
	return (0);
}
