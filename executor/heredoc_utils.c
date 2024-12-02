/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:35:16 by maustel           #+#    #+#             */
/*   Updated: 2024/11/21 16:35:16 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*-------------------------------------------------------------
Get length of expansion for example $USER -> maustel -> len = 7
---------------------------------------------------------------*/
size_t	get_len_exp_hd(char *line, char *exp, size_t index)
{
	size_t	j;
	size_t	len;

	j = 0;
	len = 0;
	while (j < index)
	{
		len++;
		j++;
	}
	while (line[j] == '$')
		j++;
	while (line[j] != '\0' && !is_quotes(line[j]) && line[j] != '$'
		&& !is_wspace(line[j]))
		j++;
	while (line[j] != '\0')
	{
		j++;
		len++;
	}
	len += ft_strlen(exp);
	return (len);
}

/*-------------------------------------------------------------
create filepath for each heredoc-temp-file
---------------------------------------------------------------*/
char	*generate_file_path(int id)
{
	char	*full_path;
	char	*nbr;

	nbr = ft_itoa(id);
	full_path = ft_strjoin(BASE_PATH, nbr);
	free (nbr);
	return (full_path);
}

/*-------------------------------------------------------------
Handle heredoc parent
---------------------------------------------------------------*/
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
		return (print_error(exit_code, NULL, NOTPRINT));
	return (exit_code);
}
