/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:32:40 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/27 15:49:20 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	replace_key(t_shell *shell, t_command *row, size_t index, size_t j)
{
	if (shell->env[index])
		free(shell->env[index]);
	shell->env[index] = safe_ft_strdup(row->args[j]);
	if (!shell->env[index])
	{
		return (-1);
	}
	return (0);
}

// replaces the existing key with the users input (USER=JESUS)

char	**append_keys(char **tmp, t_shell *shell, t_command *row)
{
	while (row->args[shell->i] != NULL)
	{
		if (valid_key_name(row->args[shell->i])
			&& (key_exists(tmp, row->args[shell->i]) == -1))
		{
			tmp[shell->j] = safe_ft_strdup(row->args[shell->i]);
			if (!tmp[shell->j])
				return (clear_all(tmp), NULL);
			shell->j++;
		}
		shell->i++;
	}
	tmp[shell->j] = NULL;
	return (tmp);
}
	// dups the remaining variables into tmp;

char	**copy_new_envs(char **tmp, t_shell *shell, t_command *row)
{
	shell->j = 0;
	while (shell->env[shell->j] != NULL)
	{
		tmp[shell->j] = safe_ft_strdup(shell->env[shell->j]);
		if (!tmp[shell->j])
			return (clear_all(tmp), NULL);
		shell->j++;
	}
	tmp = append_keys(tmp, shell, row);
	if (!tmp)
		return (NULL);
	return (tmp);
}

// dups the environment variables into tmp
// calls function to append new keys=variables into tmp

int	check_duplicate_keys(t_shell *shell, t_command *row)
{
	size_t	i;

	i = 0;
	while (row->args[i] != NULL)
	{
		if (key_exists(shell->env, row->args[i]) != -1)
		{
			if (replace_key(shell, row,
					key_exists(shell->env, row->args[i]), i) == -1)
			{
				return (-1);
			}
		}
		i++;
	}
	return (0);
}

// iterates through args and checks
// if the current string is an existing key in the og envs
// if the key exists in og envs then it calls the function to replace it

int	export_with_args(t_shell *shell, t_command *row)
{
	char	**tmp;
	int		len;

	len = 0;
	tmp = NULL;
	len = get_len_new_env(shell->env, row, shell->i);
	tmp = safe_malloc(sizeof(char *) * (len + 1));
	if (!tmp)
		return (-1);
	tmp = set_to_null(tmp, len);
	if (check_duplicate_keys(shell, row) == -1)
		return (-1);
	tmp = copy_new_envs(tmp, shell, row);
	if (!tmp)
		return (-1);
	if (shell->env)
		clear_all(shell->env);
	if (copy_env(tmp, shell) == -1)
		return (clear_all(tmp), -1);
	clear_all(tmp);
	return (0);
}
