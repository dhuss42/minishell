/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:37:26 by maustel           #+#    #+#             */
/*   Updated: 2024/10/21 15:07:37 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	handle_heredoc_input(t_exec *test, char *delimiter)
{
	char	*line;
	int		fd;

	fd = open("tmp/heredoc_temp", O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		return (print_error(errno, NULL, test));
	while (1)
	{
		line = readline("> ");
		if (ft_strncmp(line, delimiter, ft_strlen(line)) == 0)
		{
			free (line);
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
	}
	if (close(fd) == -1)
		return (print_error(errno, NULL, test));
	return (0);
}

int	handle_heredoc(t_command cmd, t_exec *test)
{
	int		i;

	if (cmd.red_symbol && cmd.filename)
	{
		i = 0;
		while(cmd.red_symbol[i] && cmd.filename[i])
		{
			if (cmd.red_symbol[i][0] == '<' && cmd.red_symbol[i][1] == '<')
			{
				if (handle_heredoc_input(test, cmd.filename[i]))
					return (1);
			}
			i++;
		}
	}
	return (0);
}
