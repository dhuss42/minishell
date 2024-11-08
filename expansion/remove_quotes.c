/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:47:50 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/21 16:05:18 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_eichhoernchen.h"

void	get_len_no_quotes(t_command *row, t_shell *expand)
{
	expand->quote = '\0';
	expand->j = 0;
	expand->len = 0;
	while (row->args[expand->i][expand->j] != '\0')
	{
		if (row->args[expand->i][expand->j] == '$' && is_quotes(row->args[expand->i][expand->j + 1]))
			expand->j++;
		if (is_quotes(row->args[expand->i][expand->j]))
		{
			expand->quote = row->args[expand->i][expand->j];
			expand->j++;
			while (row->args[expand->i][expand->j] != '\0' && row->args[expand->i][expand->j] != expand->quote)
			{
				expand->len++;
				expand->j++;
			}
			expand->j++;
		}
		else
		{
			expand->len++;
			expand->j++;
		}
	}
	// printf(MAGENTA"len no quotes: %zu\n"WHITE, expand->len);
}

int	remove_outer_quotes(t_command *row, t_shell *expand)
{
	char	*no_quotes;
	
	get_len_no_quotes(row, expand);
	no_quotes = safe_ft_calloc(expand->len + 1, sizeof(char));
	if (!no_quotes)
		return (-1);
	expand->j = 0;
	expand->k = 0;
	while (row->args[expand->i][expand->j] != '\0')
	{
		if (row->args[expand->i][expand->j] == '$' && is_quotes(row->args[expand->i][expand->j + 1]))
			expand->j++;
		if (is_quotes(row->args[expand->i][expand->j]))
		{
			expand->quote = row->args[expand->i][expand->j];
			expand->j++;
			while (row->args[expand->i][expand->j] != '\0' && row->args[expand->i][expand->j] != expand->quote)
				no_quotes[expand->k++] = row->args[expand->i][expand->j++];
			expand->j++;
		}
		else
			no_quotes[expand->k++] = row->args[expand->i][expand->j++];
	}
	if (row->args[expand->i])
		free (row->args[expand->i]);
	row->args[expand->i] = safe_ft_strdup(no_quotes);
	if (!row->args[expand->i])
		return (free(no_quotes), -1);
	if (no_quotes)
		free(no_quotes);
	return (0);
}

// function allocates memory for a string without quotes
// loops until end
// if it finds a quote it skips it in the og string, then it copies into no_quotes until it finds the matching closing quote
// skips the closing quote in og
// frees the relevant string in args** and replaces it with the string without quotes
// frees the no_quotes string


int	remove_quotes(t_list *table)
{
	t_shell		expand;
	t_command	*row;

	expand.tmp = table;
	while (expand.tmp != NULL)
	{
		row = (t_command*) expand.tmp->content;
		expand.i = 0;
		while (row->args[expand.i] != NULL)
		{
			if (remove_outer_quotes(row, &expand) == -1)
				return (-1);
			expand.i++;
		}
		expand.tmp = expand.tmp->next;
	}
	return (0);
}

// itterates through the table and the char **