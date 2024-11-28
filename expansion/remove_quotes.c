/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:47:50 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/27 16:48:32 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	remove_quotes(t_list *table, t_shell *expand)
{
	t_command	*row;

	expand->rem = false;
	expand->tmp = table;
	while (expand->tmp != NULL)
	{
		row = (t_command *) expand->tmp->content;
		if (process_quotes(row->args, expand) == -1)
			return (-1);
		if (process_quotes(row->filename, expand) == -1)
			return (-1);
		expand->tmp = expand->tmp->next;
	}
	return (0);
}
