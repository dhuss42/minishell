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

size_t	strlen_equal(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	return (i);
}

char	*compare_with_env(char *variable, char **env, char *exp)
{

	size_t	j = 0;

		while (env[j] != NULL)
		{
			if (ft_strlen(variable) - strlen_equal(env[j]) == 0)
			{
				if (ft_strncmp(variable, env[j], strlen_equal(env[j])) == 0)
				{
					return (exp = ft_substr(env[j], strlen_equal(env[j]) + 1, ft_strlen(env[j]) - strlen_equal(env[j]) - 1));
				}
			}
			j++;
		}
	return (exp);
}

// compares the variable name (PATH) to every string in the env** list
// env strings are only compared up until the equal sign =
// all env variables are built like this (PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin:/Users/dhuss/.brew/bin)
// returns when the variable and the env are equal up until the '=' sign

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
	while (row->args[expand->i][j] == '$')
		j++;
	while(row->args[expand->i][j] != '\0' && !is_quotes(row->args[expand->i][j]) && row->args[expand->i][j] != '$')
		j++;
	while(row->args[expand->i][j] != '\0')
	{
		j++;
		len++;
	}
	len += ft_strlen(exp);
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
	while(row->args[expand->i][expand->j] != '\0' && row->args[expand->i][expand->j] != '$' && !is_quotes(row->args[expand->i][expand->j]))
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
// copies everything up until the dollar sign into the tmp string
// skipps everything up until $ or quote in the og string (skipping $PATH)
// copies the expanded variable string into tmp (exp -> tmp)
// frees the expanded variable string
// moves k (the itterater in the 3 while loop) to the end of the exanded string
// copies the remainder into tmp and null terminates
// frees the string in args **
// strdups tmp into the now free position in args **
// frees tmp


void	get_expanded(char *variable, char **env, t_command *row, t_shell *expand)
{
	char	*exp = NULL;

	variable = tmp_dollar(row, expand);
	while (*variable == '$')
		variable++;
	exp = compare_with_env(variable, env, exp);
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