/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_expanded.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:37:20 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/06 15:07:14 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_eichhoernchen.h"

char	*split_echo(char *str)
{
	char	*remainder;
	char	*pos;

	pos = ft_strchr(str, ' ');
	pos++;
	remainder = malloc(sizeof(char) * (ft_strlen(pos) + 1));
	if (!remainder)
		return (NULL);
	ft_strlcpy(remainder, pos, ft_strlen(pos) + 1);
	return (remainder);
}

char	**duplicate_double_ptr(char **double_ptr)
{
	char	**duplicate;
	size_t	i;

	i = 0;
	while (double_ptr[i] != NULL)
		i++;
	duplicate = malloc(sizeof(char *) * (i + 1));
	if(!duplicate)
		return (NULL);
	i = 0;
	while (double_ptr[i] != NULL)
	{
		duplicate[i] = ft_strdup(double_ptr[i]);
		if (!duplicate[i])
		{
			clear_all(duplicate);
			return (NULL);
		}
		i++;
	}
	duplicate[i] = NULL;
	return (duplicate);
}

char	**special_dup(t_command *row, char **tmp)
{
	size_t	i;
	size_t	j;

	i = 2;
	j = 1;
	while (row->args[j] != NULL)
	{
		tmp[i] = ft_strdup(row->args[j]);
		if(!tmp[i])
		{
			clear_all(tmp);
			return (NULL);
		}
		i++;
		j++;
	}
	tmp[i] = NULL;
	return (tmp);
}

char	**tmp_args(t_command *row, char *separated)
{
	char	**tmp;
	size_t	i;

	i = 0;
	while(row->args[i] != NULL)
		i++;
	tmp = malloc(sizeof(char *) * (i + 2));
	if (!tmp)
		return (NULL);
	tmp[0] = ft_strdup("echo");
	if (!tmp[0])
		return (NULL);
	tmp[1] = ft_strdup(separated); // here for -n
	if (!tmp[1])
	{
		free(tmp[0]);
		return (NULL);
	}
	tmp = special_dup(row, tmp);
	if (!tmp)
	{
		clear_all(tmp);
		return (NULL);
	}
	return (tmp);
}

void	echo_expanded(t_shell *shell, t_command *row)
{
	char	*separated;
	char	**tmp;

	separated = split_echo(row->args[shell->i]);
	tmp = tmp_args(row, separated);
	clear_all(row->args);
	row->args = duplicate_double_ptr(tmp);
	if (!row->args)
		return ;
	clear_all(tmp);
	free(separated);
}

