/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:37:26 by maustel           #+#    #+#             */
/*   Updated: 2024/11/14 15:27:35 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

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

int	heredoc_parent(pid_t pid)
{
	int	wstatus;
	int	exit_code;

	exit_code = 0;
	if (waitpid(pid, &wstatus, 0) == -1)
		return (1);
	if (WIFEXITED(wstatus))
			exit_code = WEXITSTATUS(wstatus);
	if (WIFSIGNALED(wstatus))
		exit_code = WTERMSIG(wstatus) + 128;
	if (exit_code > 0)
		return(print_error(exit_code, NULL, NOTPRINT));
	return (exit_code);
}

void	heredoc_child(char *delimiter, int fd, char **env)
{
	char	*line;

	line = NULL;
	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		heredoc_expansion(line, env);
		if (ft_strlen(line) == ft_strlen(delimiter)
			&&ft_strncmp(line, delimiter, ft_strlen(line)) == 0)
		{
			free (line);
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free (line);
	}
	exit (0);
}

/*-------------------------------------------------------------
create one temporary file for each row if there is a heredoc
write until delimiter into file
the funciton readline has memory issues (still reachable)
see with valgrind --leak-check=full --show-leak-kinds=all
---------------------------------------------------------------*/
static int	handle_heredoc_input(char *delimiter, t_command *row, char **env)
{
	pid_t pid;
	int		fd;

	row->heredoc_file_path = generate_file_path(row->id);
	fd = open(row->heredoc_file_path, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		return (print_error(errno, row->heredoc_file_path, PRINT));
	pid = fork();
	if (pid == -1)
			return (print_error(errno, NULL, PRINT));
	else if (pid == 0)
		heredoc_child(delimiter, fd, env);
	heredoc_parent(pid);
	if (close(fd) == -1)
		return (print_error(errno, NULL, PRINT));
	return (0);
}

/*-------------------------------------------------------------
check if symbol is heredoc, then handle heredoc input
---------------------------------------------------------------*/
static int go_through_heredoc_files(t_command *row, char **env)
{
	int	i;

	i = 0;
	while(row->red_symbol[i] && row->filename[i])
	{
		if (row->red_symbol[i][0] == '<' && row->red_symbol[i][1] == '<')
		{
			if (handle_heredoc_input(row->filename[i], row, env))
				return (1);
		}
		i++;
	}
	return (0);
}

void init_content(t_command *row)
{
	row->heredoc_file_path = NULL;
	row->path = NULL;
	row->final_infile = NULL;
	row->final_outfile = NULL;
	row->final_in_red = NULL;
	row->final_out_red = NULL;
}

/*-------------------------------------------------------------
Go through table and handle each heredoc in each row
---------------------------------------------------------------*/
int	handle_heredoc(t_list *table, char **env)
{
	int			id;
	t_list		*tmp;
	t_command	*row;

	tmp = table;
	id = 0;
	signal(SIGINT, SIG_IGN);
	while(tmp)
	{
		row = (t_command *) tmp->content;
		row->id = id;
		init_content(row);
		if (row->red_symbol && row->filename)
		{
			if (go_through_heredoc_files(row, env))
				return (1);
		}
		tmp = tmp->next;
		id++;
	}
	return (0);
}
