/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_expanded.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:37:20 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/18 14:27:17 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_eichhoernchen.h"

char	*split_echo(char *str)
{
	char	*remainder;
	char	*pos;

	pos = ft_strchr(str, ' ');
	pos++;
	remainder = safe_malloc(sizeof(char) * (ft_strlen(pos) + 1));
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
	duplicate = safe_malloc(sizeof(char *) * (i + 1));
	if (!duplicate)
		return (NULL);
	i = 0;
	while (double_ptr[i] != NULL)
	{
		duplicate[i] = safe_ft_strdup(double_ptr[i]);
		if (!duplicate[i])
			return (clear_all(duplicate), NULL);
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
		tmp[i] = safe_ft_strdup(row->args[j]);
		if (!tmp[i])
			return (clear_all(tmp), NULL);
		i++;
		j++;
	}
	tmp[i] = NULL;
	return (tmp);
}

// handle -n -nnn inside string

// check if next char is -
// while(n) i++;
// if char is '\0' or ' ' stop

// ---> not sure if effort is worth it tbh

char	**tmp_args(t_command *row, char *separated)
{
	char	**tmp;
	size_t	i;

	i = 0;
	while (row->args[i] != NULL)
		i++;
	tmp = safe_malloc(sizeof(char *) * (i + 2));
	if (!tmp)
		return (NULL);
	tmp[0] = safe_ft_strdup("echo");
	if (!tmp[0])
		return (NULL);
	// function handling -n -nnnn inside the remainder string
	tmp[1] = safe_ft_strdup(separated);
	if (!tmp[1])
		return (clear_all(tmp), NULL);
	tmp = special_dup(row, tmp);
	if (!tmp)
		return (NULL);
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
