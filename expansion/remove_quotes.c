/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:47:50 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/27 12:43:10 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_len_no_quotes(char **input, t_shell *e)
{
	e->quote = '\0';
	e->j = 0;
	e->len = 0;
	while (input[e->i][e->j] != '\0')
	{
		if (input[e->i][e->j] == '$' && is_quotes(input[e->i][e->j + 1]))
			e->j++;
		if (is_quotes(input[e->i][e->j]))
		{
			e->quote = input[e->i][e->j];
			e->j++;
			while (input[e->i][e->j] != '\0'
				&& input[e->i][e->j] != e->quote)
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

int	quotes_copy_free(char **input, t_shell *e, char *no_quotes)
{
	if (input[e->i])
		free (input[e->i]);
	input[e->i] = safe_ft_strdup(no_quotes);
	if (!input[e->i])
		return (free(no_quotes), -1);
	if (no_quotes)
		free(no_quotes);
	return (0);
}

void	remove_quotes_loop(char **input, t_shell *e, char *no_quotes)
{
	while (input[e->i][e->j] != '\0')
	{
		if (input[e->i][e->j] == '$' && is_quotes(input[e->i][e->j + 1]))
			e->j++;
		if (is_quotes(input[e->i][e->j]))
		{
			e->rem = true;
			e->quote = input[e->i][e->j];
			e->j++;
			while (input[e->i][e->j] != '\0'
				&& input[e->i][e->j] != e->quote)
			{
				no_quotes[e->k++] = input[e->i][e->j++];
			}
			e->j++;
		}
		else
			no_quotes[e->k++] = input[e->i][e->j++];
	}
}

int	remove_outer_quotes(char **input, t_shell *e)
{
	char	*no_quotes;

	get_len_no_quotes(input, e);
	no_quotes = safe_ft_calloc(e->len + 1, sizeof(char));
	if (!no_quotes)
		return (-1);
	e->j = 0;
	e->k = 0;
	remove_quotes_loop(input, e, no_quotes);
	if (quotes_copy_free(input, e, no_quotes) == -1)
		return (-1);
	return (0);
}

int	process_quotes(char **array, t_shell *expand)
{
	expand->i = 0;
	while (array[expand->i] != NULL)
	{
		if (remove_outer_quotes(array, expand) == -1)
			return (-1);
		expand->i++;
	}
	return (0);
}

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

// itterates through the table and the char **

