/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switcheroo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:41:27 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/22 15:44:14 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_eichhoernchen.h"

size_t  get_len_exp(t_command *row, char *exp, t_shell *expand)
{
	size_t  j;
	size_t  len;

	j = 0;
	len = 0;
	while(j < expand->k)
	{
		len++;
		j++;
	}
	// printf(BLUE"len up to k: %zu\n"WHITE, len);
	while (row->args[expand->i][j] == '$')
		j++;
	// printf(BLUE"len after $ skip: %zu\n"WHITE, len);
	while(row->args[expand->i][j] != '\0' && !is_quotes(row->args[expand->i][j]) && row->args[expand->i][j] != '$' && !is_wspace(row->args[expand->i][j]))
		j++;
	// printf(BLUE"len after variale name skip: %zu\n"WHITE, len);
	while(row->args[expand->i][j] != '\0')
	{
		j++;
		len++;
	}
	// printf(BLUE"len with remainder: %zu\n"WHITE, len);
	len += ft_strlen(exp);
	// printf(BLUE"len with exp: %zu\n"WHITE, len);
	return (len);
}

// gets the length up until the dollar sign (aaaa$HOME)
// skipps adjacent $ (aa$$HOME)
// skipps until closing quote or $ sign ($HOME$)
// gets the len of the remainder of the string ($HOME$a)
// adds the length of the expanded string

char	*copy_into_tmp(t_command *row, char *exp, t_shell *expand, char *tmp)
{
	size_t	iterate;
	size_t	index;

	expand->j = 0;
	iterate = 0;
	index = 0;
	while(expand->j < expand->k)
		tmp[iterate++] = row->args[expand->i][expand->j++];
	expand->j++;
	while(row->args[expand->i][expand->j] != '\0' && row->args[expand->i][expand->j] != '$' && !is_quotes(row->args[expand->i][expand->j]) && !is_wspace(row->args[expand->i][expand->j]))
		expand->j++;
	while (exp[index] != '\0')
		tmp[iterate++] = exp[index++];
	if (exp)
		free(exp);
	expand->k = iterate;
	while (iterate < expand->len)
	{
		tmp[iterate] = row->args[expand->i][expand->j];
		iterate++;
		expand->j++;
	}
	tmp[iterate] = '\0';
	return (tmp);
}

// copies everything up until the dollar sign into the tmp string
// skipps everything up until $ or quote in the og string (skipping $PATH)
// copies the expanded variable string into tmp (exp -> tmp)
// frees the expanded variable string
// moves k (the itterater in the 3 while loop) to the end of the exanded string
// copies the remainder into tmp and null terminates

void	switcheroo(t_command *row, char *exp, t_shell *expand)
{
	char	*tmp;

	expand->len = get_len_exp(row, exp, expand);
	tmp = ft_calloc(expand->len + 1, sizeof(char));
	if (!tmp)
		return ;
	tmp = copy_into_tmp(row, exp, expand, tmp);
	if (row->args[expand->i])
	{
		free(row->args[expand->i]);
		row->args[expand->i] = NULL;
	}
	row->args[expand->i] = ft_strdup(tmp);
	if (!row->args[expand->i])
		return ;
	if (tmp)
		free(tmp);
}


// switcheroo
// gets len of the complete expanded string
// allocates the tmp char in which the expanded string will be copied
// frees the string in args **
// strdups tmp into the now free position in args **
// frees tmp

char	*tmp_dollar(t_command *row, t_shell *expand)
{
	char	*tmp;
	size_t	index;

	tmp = NULL;
	index = expand->k;
	while (row->args[expand->i][index] == '$' /* || */ /* is_wspace(row->args[expand->i][index]) */) // need to handle when there are chars before the variable in the quote
		index++;
	expand->j = index;
	while (row->args[expand->i][expand->j] != '\0' && !is_quotes(row->args[expand->i][expand->j]) && row->args[expand->i][expand->j] != '$' && !is_wspace(row->args[expand->i][expand->j]))
		expand->j++;
	tmp = malloc(sizeof(char) * (expand->j + 1));
	if (!tmp)
		return (NULL);
	expand->j = 0;
	while (row->args[expand->i][index] != '\0' && row->args[expand->i][index] != '\"' && row->args[expand->i][index] != '\'' && row->args[expand->i][index] != '$' && !is_wspace(row->args[expand->i][index]))
		tmp[expand->j++] = row->args[expand->i][index++];
	tmp[expand->j] = '\0';
	if (row->args[expand->i][index] == expand->quote)
		index++;
	// printf(GREEN"tmp: %s\n"WHITE, tmp);
	// printf(GREEN"len tmp: %zu\n"WHITE, ft_strlen(tmp));
	return (tmp);
}

// tmp_dolalr
// creates a searchable variable name to compare to the env variable list
// index copies the position of index expand->k this is necessary so that expand-> remembers the starting position of variable for later use
// skipps adjancent $ ($$PATH)
// gets the length of the string ($PATH)
// allocates the tmp string
// copies into tmp (boraders are " ' $ ($PATH$) and \0)
// moves og string past closing quote if there is one

void	get_expanded(char *variable, char **env, t_command *row, t_shell *expand)
{
	char	*exp = NULL;

	variable = tmp_dollar(row, expand);
	while (*variable == '$') // not sure if I need this here (test later on)
		variable++;
	exp = compare_with_env(variable, env, exp);
	printf(RED"exp: %s\n", exp);
	if (!exp)
		exp = ft_strdup("");
	switcheroo(row, exp, expand);
	if (variable)
	{
		free (variable);
		variable = NULL;
	}
}

// moves past the dollar so variable becomes searchable (PATH)
// compares with env list
// if exp is empty because there is no match then it should be an empty string ($PATHaaaa)
// calls the switch