/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:41:16 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/19 15:07:05 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	double_quotes(t_command *r, t_shell *ex, char **env)
{
	char	*tmp;

	tmp = NULL;
	ex->quote = r->args[ex->i][ex->k];
	ex->k++;
	while (r->args[ex->i][ex->k] != ex->quote && r->args[ex->i][ex->k] != '\0')
	{
		if (r->args[ex->i][ex->k] == '$'
			&& ft_isalnum(r->args[ex->i][ex->k + 1]))
		{
			if (get_expanded(tmp, env, r, ex) == -1)
				return (-1);
		}
		else if (r->args[ex->i][ex->k] == '$'
			&& (r->args[ex->i][ex->k + 1] == '?'))
		{
			if (get_exit_code(tmp, r, ex) == -1)
				return (-1);
		}
		else
			ex->k++;
	}
	if (r->args[ex->i][ex->k] == '\"')
		ex->k++;
	return (0);
}

// here
// sets quote to the current quote symbol in the og string
// iterates through the string until it
// eaches the end or the matching closing quote

void	skip_single_quotes(t_command *row, t_shell *ex)
{
	if (row->args[ex->i][ex->k] == '\'')
	{
		ex->k++;
	}
	while (row->args[ex->i][ex->k] != '\'' && row->args[ex->i][ex->k] != '\0')
	{
		ex->k++;
	}
	if (row->args[ex->i][ex->k] == '\'')
	{
		ex->k++;
	}
}

int	check_for_expansion(t_command *r, t_shell *e, char **env)
{
	char	*tmp;

	e->k = 0;
	e->quote = '\0';
	tmp = NULL;
	while (r->args[e->i][e->k] != '\0')
	{
		if (r->args[e->i][e->k] == '\"' && contains_dollar(r->args[e->i], e->k))
		{
			if (double_quotes(r, e, env) == -1)
				return (-1);
		}
		else if (r->args[e->i][e->k] == '\'')
			skip_single_quotes(r, e);
		else if (r->args[e->i][e->k] == '$' && ft_isalnum(r->args[e->i][e->k + 1]))
		{
			if (get_expanded(tmp, env, r, e) == -1)
				return (-1);
		}
		else if (r->args[e->i][e->k] == '$' && (r->args[e->i][e->k + 1] == '?'))
		{
			if (get_exit_code(tmp, r, e) == -1)
				return (-1);
		}
		else
			e->k++;
	}
	return (0);
}

// check for expansion
// goes through the single string
// 1. checks if the current position of the string is
//		a double quote and if the string still contains dollars
// if yes it goes into double_quotes with "
// 2. checks if the current position of the string is a single
//		quote and if it should expand (nbr of consequetive double_quotes % 2)
// if yes it goes into double_quotes with '
// 3. is the case where single double_quotes should not expand
// if this is true then it skipps all the chars until the closing quote
// 4. checks for $
// if yes it goes into tmp_dollar (creates searchable variable name)
//		and get_expanded (gets the expansion)
// 5. moves the string index if nothing is the case

int	iterate_table(t_list *table, char **env)
{
	t_shell		expand;
	t_command	*row;

	expand.tmp = table;
	while (expand.tmp != NULL)
	{
		row = (t_command *)expand.tmp->content;
		expand.i = 0;
		while (row->args[expand.i] != NULL)
		{
			if (check_for_expansion(row, &expand, env) == -1)
				return (-1);
			expand.i++;
		}
		expand.tmp = expand.tmp->next;
	}
	return (0);
}
