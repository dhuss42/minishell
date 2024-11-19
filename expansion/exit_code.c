/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:36:31 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/19 12:09:03 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_int_length(int num)
{
	int	len;

	len = 0;
	if (num == 0)
		return (1);
	if (num < 0)
	{
		len++;
		num = -num;
	}
	while (num > 0)
	{
		len++;
		num /= 10;
	}
	return (len);
}

char	*copy_exit_code(t_shell *expand, t_command *row, char *tmp)
{
	size_t	len;
	size_t	index;
	char	*tmp_ec;

	len = 0;
	expand->j = 0;
	index = 0;
	while (expand->j < expand->k)
		tmp[len++] = row->args[expand->i][expand->j++];
	expand->j += 2;
	tmp_ec = ft_itoa(print_error(-1, NULL, NOTPRINT));
	if (!tmp_ec)
	{
		print_error(errno, NULL, PRINT);
		return (NULL); // not sure if tmp should be freed
	}
	expand->k += ft_strlen(tmp_ec);
	while (tmp_ec[index] != '\0')
		tmp[len++] = tmp_ec[index++];
	free(tmp_ec);
	while (row->args[expand->i][expand->j] != '\0')
		tmp[len++] = row->args[expand->i][expand->j++];
	tmp[len] = '\0';
	return (tmp);
}

int	update_arg_and_free(t_shell *expand, t_command *row, char *tmp)
{
	if (row->args[expand->i])
		free(row->args[expand->i]);
	row->args[expand->i] = safe_ft_strdup(tmp);
	if (!row->args[expand->i])
		return (free(tmp), -1);
	if (tmp)
	{
		free(tmp);
		tmp = NULL;
	}
	return (0);
}

int	get_exit_code(char *tmp, t_command *row, t_shell *expand)
{
	int	exit_code;
	int	len;

	exit_code = print_error(-1, NULL, NOTPRINT);
	len = get_int_length(exit_code);
	len += ft_strlen(row->args[expand->i]) - 2;
	tmp = safe_malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (-1);
	tmp = copy_exit_code(expand, row, tmp);
	if (!tmp)
		return (-1);
	if (update_arg_and_free(expand, row, tmp) == -1)
		return (-1);
	return (0);
}

// gets the current exit_code
// get the length of the exit code
// allocates tmp_ec to store the exit_code
// takes the length of th exit code and adds that of the args string minus $?
// allocates a tmp with this length in which the entire string will be stored
// copies up the $ in tmp and moves iterator j passt ?
// itoa to get exitcode string in tmp_ec
// copies tmp_ec into tmp
// copies remainder of args into tmp
// frees args
// strdups tmp into args
// frees tmp
