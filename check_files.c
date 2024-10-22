/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:07:26 by maustel           #+#    #+#             */
/*   Updated: 2024/10/22 16:08:11 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/*-------------------------------------------------------------
create file with read/write permission
---------------------------------------------------------------*/
int	create_file(char *filename, t_exec *test)
{
	int	fd;

	fd = 0;
	if (ft_strlen(filename) == 0)
		return (print_error(EPERM, filename, test));
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (print_error(errno, filename, test));
	if (close(fd) == -1)
		return (print_error(errno, filename, test));
	return (0);
}

/*-------------------------------------------------------------
check if infile exists and there is permission to read file
---------------------------------------------------------------*/
int	check_input_files(t_command *row, t_exec *test, int i)
{
	if (row->red_symbol[i][1] == '\0')
	{
		if (access(row->filename[i], F_OK) == -1)
			return (print_error(EPERM, row->filename[i], test));
		else if (access(row->filename[i], R_OK) == -1)
			return (print_error(EPERM, row->filename[i], test));
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
int	check_output_files(t_command *row, t_exec *test, int i)
{
	struct stat filestat;

	if (access(row->filename[i], F_OK) == -1)
	{
		if (create_file(row->filename[i], test))
			return (1);
	}
	stat(row->filename[i], &filestat);
	if (S_ISDIR(filestat.st_mode))
		return (print_error(E_ISDIRECTORY, row->filename[i], test));
	if (access(row->filename[i], W_OK) == -1)
		return (print_error(E_NOPERMISSION, row->filename[i], test));
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
int	check_files(t_list *table, t_exec *test)
{
	int			i;
	t_list		*tmp;
	t_command	*row;

	tmp = table;
	while (tmp)
	{
		row = (t_command *)tmp->content;
		init_final_red_files(row);
		if (!row->filename || !row->red_symbol)
			return (1);
		i = 0;
		while (row->filename[i])
		{
			write (1, "a", 1); //ERROR HERE!
			if (row->red_symbol[i] && row->red_symbol[i][0] == '>')
			{
				if (check_output_files(row, test, i))
					return (2);
			}
			else if (row->red_symbol[i] && row->red_symbol[i][0] == '<')
			{
				if (check_input_files(row, test, i))
					return (3);
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (0);

	// if (example.filename && example.red_symbol)
	// {
	// 	i = 0;
	// 	while (example.filename[i])
	// 	{
	// 		if (example.red_symbol[i] && example.red_symbol[i][0] == '>')
	// 		{
	// 			if (check_output_files(example, test, i))
	// 				return (1);
	// 		}
	// 		else if (example.red_symbol[i] && example.red_symbol[i][0] == '<')
	// 		{
	// 			if (check_input_files(example, test, i))
	// 				return (2);
	// 		}
	// 		i++;
	// 	}
	// }
}
