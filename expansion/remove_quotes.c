/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:47:50 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/19 12:09:17 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_len_no_quotes(t_command *r, t_shell *ex)
{
	ex->quote = '\0';
	ex->j = 0;
	ex->len = 0;
	while (r->args[ex->i][ex->j] != '\0')
	{
		if (r->args[ex->i][ex->j] == '$' && is_quotes(r->args[ex->i][ex->j + 1]))
			ex->j++;
		if (is_quotes(r->args[ex->i][ex->j]))
		{
			ex->quote = r->args[ex->i][ex->j];
			ex->j++;
			while (r->args[ex->i][ex->j] != '\0' && r->args[ex->i][ex->j] != ex->quote)
			{
				ex->len++;
				ex->j++;
			}
			ex->j++;
		}
		else
		{
			ex->len++;
			ex->j++;
		}
	}
}

int	remove_outer_quotes(t_command *r, t_shell *ex)
{
	char	*no_quotes;

	get_len_no_quotes(r, ex);
	no_quotes = safe_ft_calloc(ex->len + 1, sizeof(char));
	if (!no_quotes)
		return (-1);
	ex->j = 0;
	ex->k = 0;
	while (r->args[ex->i][ex->j] != '\0')
	{
		if (r->args[ex->i][ex->j] == '$' && is_quotes(r->args[ex->i][ex->j + 1]))
			ex->j++;
		if (is_quotes(r->args[ex->i][ex->j]))
		{
			ex->quote = r->args[ex->i][ex->j];
			ex->j++;
			while (r->args[ex->i][ex->j] != '\0' && r->args[ex->i][ex->j] != ex->quote)
				no_quotes[ex->k++] = r->args[ex->i][ex->j++];
			ex->j++;
		}
		else
			no_quotes[ex->k++] = r->args[ex->i][ex->j++];
	}
	if (r->args[ex->i])
		free (r->args[ex->i]);
	r->args[ex->i] = safe_ft_strdup(no_quotes);
	if (!r->args[ex->i])
		return (free(no_quotes), -1);
	if (no_quotes)
		free(no_quotes);
	return (0);
}

// function allocates memory for a string without quotes
// loops until end
// if it finds a quote it skips it in the og string,
// then it copies into no_quotes until it finds the matching closing quote
// skips the closing quote in og
// frees the relevant string in args** and
// replaces it with the string without quotes
// frees the no_quotes string

int	remove_quotes(t_list *table)
{
	t_shell		expand;
	t_command	*row;

	expand.tmp = table;
	while (expand.tmp != NULL)
	{
		row = (t_command *) expand.tmp->content;
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