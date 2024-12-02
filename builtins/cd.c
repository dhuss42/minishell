/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:07:34 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/20 12:18:04 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*search_env(char **env, char *key)
{
	size_t	i;
	char	*str;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], key, strlen_equal(env[i])) == 0)
		{
			str = safe_ft_substr(env[i], strlen_equal(env[i]) + 1,
					ft_strlen(env[i]) - strlen_equal(env[i]) - 1);
			if (!str)
				return (NULL);
			return (str);
		}
		i++;
	}
	return (NULL);
}

// get HOME key
// compare with env and get string following the = sign
// use the string as the arg for cddir
// check for error if HOME does not exist or is not set

int	cd_no_args(t_shell *shell, t_command *row, char *current_dir)
{
	char	*no_args;

	no_args = search_env(shell->env, "HOME");
	if (!no_args)
		return (print_error(E_NOTSET, "HOME", PRINT), -1);
	if (no_args[0] != '\0')
	{
		if (chdir(no_args) == -1)
			return (print_error(errno, row->args[1], PRINT));
	}
	if (update_oldpwd(shell, current_dir) != 0)
		return (-1);
	if (update_pwd(shell) != 0)
		return (-1);
	if (no_args)
		free(no_args);
	return (0);
}

int	ft_cd(t_shell *shell, t_command *row)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
	{
		return (print_error(errno, NULL, PRINT));
	}
	if (!row->args[1])
	{
		if (cd_no_args(shell, row, current_dir) != 0)
			return (free(current_dir), -1);
	}
	else if (row->args[1])
	{
		if (chdir(row->args[1]) == -1)
			return (free(current_dir),
				print_error(E_DIRNOEXIST, row->args[1], PRINT), -1);
		if (update_oldpwd(shell, current_dir) != 0)
			return (free(current_dir), -1);
		if (update_pwd(shell) != 0)
			return (free(current_dir), -1);
	}
	return (0);
}

// functions checks whether cd has an argument
// if cd has an argument it calls cd_no_args
// whcih moves the current directory to $HOME
