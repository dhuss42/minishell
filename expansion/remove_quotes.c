/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:47:50 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/19 15:34:09 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_len_no_quotes(t_command *r, t_shell *e)
{
	e->quote = '\0';
	e->j = 0;
	e->len = 0;
	while (r->args[e->i][e->j] != '\0')
	{
		if (r->args[e->i][e->j] == '$' && is_quotes(r->args[e->i][e->j + 1]))
			e->j++;
		if (is_quotes(r->args[e->i][e->j]))
		{
			e->quote = r->args[e->i][e->j];
			e->j++;
			while (r->args[e->i][e->j] != '\0'
				&& r->args[e->i][e->j] != e->quote)
			{
				e->len++;
				e->j++;
			}
			e->j++;
		}
		else
		{
			e->len++;
			e->j++;
		}
	}
}

int	quotes_copy_free(t_command *r, t_shell *e, char *no_quotes)
{
	if (r->args[e->i])
		free (r->args[e->i]);
	r->args[e->i] = safe_ft_strdup(no_quotes);
	if (!r->args[e->i])
		return (free(no_quotes), -1);
	if (no_quotes)
		free(no_quotes);
	return (0);
}

void	remove_quotes_loop(t_command *r, t_shell *e, char *no_quotes)
{
	while (r->args[e->i][e->j] != '\0')
	{
		if (r->args[e->i][e->j] == '$' && is_quotes(r->args[e->i][e->j + 1]))
			e->j++;
		if (is_quotes(r->args[e->i][e->j]))
		{
			e->quote = r->args[e->i][e->j];
			e->j++;
			while (r->args[e->i][e->j] != '\0'
				&& r->args[e->i][e->j] != e->quote)
			{
				no_quotes[e->k++] = r->args[e->i][e->j++];
			}
			e->j++;
		}
		else
			no_quotes[e->k++] = r->args[e->i][e->j++];
	}
}

int	remove_outer_quotes(t_command *r, t_shell *e)
{
	char	*no_quotes;

	get_len_no_quotes(r, e);
	no_quotes = safe_ft_calloc(e->len + 1, sizeof(char));
	if (!no_quotes)
		return (-1);
	e->j = 0;
	e->k = 0;
	remove_quotes_loop(r, e, no_quotes);
	if (quotes_copy_free(r, e, no_quotes) == -1)
		return (-1);
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