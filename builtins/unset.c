/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:06:37 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/06 15:12:26 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

void	get_len_unset(t_shell *shell, t_command *row)
{
	size_t	j;
	size_t	k;
	size_t	counter;

	counter = 0;
	k = shell->i;
	while (row->args[k] != NULL)
	{
		j = 0;
		while (shell->env[j] != NULL)
		{
			if (ft_strncmp(row->args[k], shell->env[j], strlen_equal(shell->env[j])) == 0)
				counter++;
			j++;
		}
		k++;
	}
	shell->len = j - counter;
}

int	finalise_unset(t_shell *shell, char **tmp)
{
	if (shell->env)
		clear_all(shell->env);
	copy_env(tmp, shell);
	if (!shell->env)
	{
		clear_all(tmp);
		return (-1);
	}
	clear_all(tmp);
	return (0);
}
// tidies up the allocates memory

bool should_copy_env_var(t_command *row, char *var, size_t unset_index)
{
	while (row->args[unset_index] != NULL)
	{
		if (ft_strncmp(row->args[unset_index], var, strlen_equal(var)) == 0)
			return (false);
		unset_index++;
	}
	return (true);
}
// determines if an envrionment variable should be copied or not
// compares each variable in shell-env with row->args
// if they match the variable should not be copied


int	copy_unset_varibles(t_shell *shell, t_command *row, char **tmp)
{
	size_t  j;
	size_t  k;

	j = 0;
	k = 0;
	while (shell->env[k] != NULL)
	{
		if (should_copy_env_var(row, shell->env[k], shell->i))
		{
			tmp[j] = ft_strdup(shell->env[k]);
			if (!tmp[j])
			{
				clear_all(tmp);
				return (-1);
			}
			j++;
		}
		k++;
	}
	tmp[j] = NULL;
	return (0);
}
// mangages the copying of non-unset environment variables tmp
// iterates through envs calling should_copy_env_var to determine if current 
// variable should be copied into tmp

int ft_unset(t_shell *shell, t_command *row)
{
	char	**tmp;

	get_len_unset(shell, row);
	tmp = (char **)safe_malloc(sizeof(char *) * shell->len + 1);
	if (!tmp)
		return (-1);
	if (copy_unset_varibles(shell, row, tmp) == -1)
		return (-1);
	return (finalise_unset(shell, tmp));
}

// allocates tmp with safe_malloc
// 