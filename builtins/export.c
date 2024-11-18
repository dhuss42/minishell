/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:06:50 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/18 15:08:52 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

int	replace_key(t_shell *shell, t_command *row, size_t index, size_t j)
{
	// printf(MAGENTA"replacing: %s at [%zu] in env with %s at [%zu] in args \n", shell->env[index], index, row->args[j], j);
	// printf(MAGENTA"[%zu]row->args: %s\n"WHITE, j, row->args[j]);
	// printf(MAGENTA"[%zu]shell->k\n"WHITE, shell->k);
	if (shell->env[index])
		free(shell->env[index]);
	shell->env[index] = safe_ft_strdup(row->args[j]);
	if (!shell->env[index])
	{
		// unsure about freeing
		return (-1);
	}
	// printf(CYAN"[%zu] ENV shell->env: %s\n"WHITE, index, shell->env[index]);
	return (0);
}

// replaces the existing key with the users input (USER=JESUS)

char	**append_keys(char **tmp, t_shell *shell, t_command *row)
{
	while (row->args[shell->i] != NULL)
	{
		if (valid_key_name(row->args[shell->i]) && (key_exists(tmp, row->args[shell->i]) == -1))
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
			if (replace_key(shell, row, key_exists(shell->env, row->args[i]), i) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}

// iterates through args and checks if the current string is an existing key in the og envs
// if the key exists in og envs then it calls the function to replace it

int	export_with_args(t_shell *shell, t_command *row)
{
	char	**tmp;
	int		len;

	len = 0;
	tmp = NULL;
	len = get_len_new_env(shell->env, row, shell->i);
	if (len == -1)
		return (-1);
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

int	ft_export(t_shell *shell, t_command *row)
{
	shell->i++;
	if (row->args[shell->i] == NULL)
	{
		if (export_no_argument(shell) == -1)
			return (-1);
		else
			return (0);
	}
	else
	{
		if (export_with_args(shell, row) == -1)
			return (-1);
		else
			return (0);
	}
}

// gets length of the new double char array that will hold all the keys=variables
// allocates that double char array (tmp)
// checks if the keys typed by User exist and replaces them in the og envs
// copies these envs into tmp & appends the user's input if its valid
// frees original envs
// copies tmp into envs
