/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:37:26 by maustel           #+#    #+#             */
/*   Updated: 2024/10/22 14:40:28 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/*-------------------------------------------------------------
create filepath for each heredoc-temp-file
---------------------------------------------------------------*/
char*	generate_file_path(int id)
{
	char	*full_path;
	char	*nbr;

	nbr = ft_itoa(id);
	full_path = ft_strjoin(BASE_PATH, nbr);
	free (nbr);
	return (full_path);
}

/*-------------------------------------------------------------
create one temporary file for each row if there is a heredoc
write until delimiter into file
the funciton readline has memory issues (still reachable)
see with valgrind --leak-check=full --show-leak-kinds=all
---------------------------------------------------------------*/
static int	handle_heredoc_input(t_exec *test, char *delimiter, t_command *row)
{
	char	*line;
	int		fd;

	row->heredoc_file_path = generate_file_path(row->id);
	fd = open(row->heredoc_file_path, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		return (print_error(errno, NULL, test));
	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(line)) == 0)
		{
			free (line);
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free (line);
	}
	if (close(fd) == -1)
		return (print_error(errno, NULL, test));
	return (0);
}

/*-------------------------------------------------------------
Go through table and handle each heredoc in each row
---------------------------------------------------------------*/
int	handle_heredoc(t_list *table, t_exec *test)
{
	int			i;
	int			id;
	t_list		*tmp;
	t_command	*row;

	tmp = table;
	id = 0;
	while(tmp)
	{
		row = (t_command *) tmp->content;
		row->id = id;
		if (!row->red_symbol || !row->filename)
			return (1);
		i = 0;
		while(row->red_symbol[i] && row->filename[i])
		{
			if (row->red_symbol[i][0] == '<' && row->red_symbol[i][1] == '<')
			{
				if (handle_heredoc_input(test, row->filename[i], row))
					return (2);
			}
			i++;
		}
		tmp = tmp->next;
		id++;
	}
	return (0);
	// if (cmd.red_symbol && cmd.filename)
	// {
	// 	i = 0;
	// 	while(cmd.red_symbol[i] && cmd.filename[i])
	// 	{
	// 		if (cmd.red_symbol[i][0] == '<' && cmd.red_symbol[i][1] == '<')
	// 		{
	// 			if (handle_heredoc_input(test, cmd.filename[i]))
	// 				return (1);
	// 		}
	// 		i++;
	// 	}
	// }
}
