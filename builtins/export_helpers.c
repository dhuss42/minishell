/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:07:04 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/19 12:35:42 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	has_equal(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

bool	valid_key_name(char *str)
{
	size_t	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
	{
		return (false);
	}
	i++;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
		{
			return (false);
		}
		i++;
	}
	return (true);
}

// checks if the key name is valid
// key cnnot be numeric
// key cannot contain a minus

int	key_exists(char **env, char *key)
{
	size_t	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(key, env[i], strlen_equal(env[i])) == 0)
			return (i);
		i++;
	}
	return (-1);
}

// checks if the current key already exists in the og envs
// returns index when match is found
// returns -1 when they don't match

int	get_len_new_env(char **env, t_command *row, size_t i)
{
	int	count;

	count = 0;
	while (env[count] != NULL)
		count++;
	while (row->args[i] != NULL)
	{
		if (valid_key_name(row->args[i])
			&& (key_exists(env, row->args[i]) == -1))
		{
			count++;
		}
		else if (!valid_key_name(row->args[i]))
		{
			print_error(E_NOTVALIDIDENT, row->args[i], PRINT);
		}
		i++;
	}
	return (count);
}

// counts len of current env variables
// iterates through User input (args)
// if the structure is valid a counter is added

char	**set_to_null(char **tmp, size_t len)
{
	size_t	j;

	j = 0;
	while (j <= len)
	{
		tmp[j] = NULL;
		j++;
	}
	return (tmp);
}
