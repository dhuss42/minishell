/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:24:16 by maustel           #+#    #+#             */
/*   Updated: 2024/10/02 15:19:14 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	**allocate_append_array(char **split_paths)
{
	int		j;
	char	**append;

	j = 0;
	while (split_paths[j] != NULL)
		j++;
	append = malloc(sizeof(char *) * (j + 1));
	return (append);
}

char	*concatenate_path_cmd(char *path, char *cmd)
{
	char	*slash;
	char	*full_path;

	slash = ft_strjoin(path, "/");
	if (!slash)
		return (NULL);
	full_path = ft_strjoin(slash, cmd);
	free(slash);
	return (full_path);
}

/*
	for each possible path in split_paths**:
	concatinate path + '/' + command --> /usr/bin + '/' + ls = /usr/bin/ls
*/
char	**add_slash_cmd(char **split_paths, char *cmd)
{
	int		i;
	char	**append;

	i = 0;
	append = allocate_append_array(split_paths);
	if (!append)
		return (NULL);
	while (split_paths[i] != NULL)
	{
		append[i] = concatenate_path_cmd(split_paths[i], cmd);
		if (!append[i])
			return (NULL);
		i++;
	}
	append[i] = NULL;
	return (append);
}
/*
	X_OK for execute/search permission
	F_OK existence test
	0 sucessful
*/
char	*check_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		if ((access(cmd[i], F_OK) == 0) && (access(cmd[i], X_OK) == 0))
			return (cmd[i]);
		i++;
	}
	return (NULL);
}

/*
	get all env paths where command could be
	get first '/' and split into small paths between the ':'
	/usr/local/bin:/usr/bin: --> /usr/local/bin  --  /usr/bin
*/
char	*get_path(char *cmd, char **envp)
{
	t_get_path	gp;

	gp.append = NULL;
	if (envp[0] == NULL)
		return (NULL);
	gp.big_path = getenv("PATH");
	if (gp.big_path == NULL)
		return (NULL);		//something with E_CUSTOM_ARGC
	gp.move = ft_strchr(gp.big_path, '/');
	gp.split_paths = ft_split(gp.move, ':');
	if (!gp.split_paths)
		return (NULL);
	gp.append = add_slash_cmd(gp.split_paths, cmd);
	gp.path = check_cmd(gp.append);
	if (gp.path == NULL)
		return (NULL);
	return (gp.path);
}