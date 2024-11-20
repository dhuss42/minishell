/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:44:28 by maustel           #+#    #+#             */
/*   Updated: 2024/11/14 14:44:28 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*-------------------------------------------------------------
Get length of expansion for example $USER -> maustel -> len = 7
---------------------------------------------------------------*/
size_t  get_len_exp_hd(char *line, char *exp, size_t index)
{
	size_t  j;
	size_t  len;

	j = 0;
	len = 0;
	while(j < index)
	{
		len++;
		j++;
	}
	while (line[j] == '$')
		j++;
	while(line[j] != '\0' && !is_quotes(line[j]) && line[j] != '$' && !is_wspace(line[j]))
		j++;
	while(line[j] != '\0')
	{
		j++;
		len++;
	}
	len += ft_strlen(exp);
	return (len);
}

/*-------------------------------------------------------------
puts everything together into tmp
---------------------------------------------------------------*/
char	*copy_into_tmp_hd(char *line, char *exp, size_t index, char *tmp)
{
	size_t	iterate;
	size_t		j;
	size_t		i;
	size_t		len;

	iterate = 0;
	j = 0;
	i = 0;
	len = get_len_exp_hd(line, exp, index);
	while(j < index)
		tmp[iterate++] = line[j++];
	j++;
	while(line[j] != '\0' && line[j] != '$' && !is_quotes(line[j])
		&& !is_wspace(line[j]))
			j++;
	while (exp[i] != '\0')
		tmp[iterate++] = exp[i++];
	while (iterate < len)
	{
		tmp[iterate] = line[j];
		iterate++;
		j++;
	}
	tmp[iterate] = '\0';
	return (tmp);
}

/*-------------------------------------------------------------
writes expanded string into new_line
---------------------------------------------------------------*/
char	*switcheroo_hd(char *line, char *exp, size_t index)
{
	char		*new_line;
	size_t		len;

	new_line = NULL;
	len = get_len_exp_hd(line, exp, index);
	new_line = safe_ft_calloc(len + 1, sizeof(char));
	if (!new_line)
		return (NULL);
	new_line = copy_into_tmp_hd(line, exp, index, new_line);
	if (exp)
		free(exp);
	if (line)
	{
		free(line);
		line = NULL;
	}
	return (new_line);
}

/*-------------------------------------------------------------
creates a searchable variable name to compare to the env variable list
it copies the position of index. this is necessary so that
expand-> remembers the starting position of variable for later use
skipps adjancent $ ($$PATH)
gets the length of the string ($PATH)
allocates the tmp string
copies into tmp (boraders are " ' $ ($PATH$) and \0)
moves og string past closing quote if there is one
---------------------------------------------------------------*/
char	*get_key_hd(char *line, size_t index)
{
	char	*tmp;
	size_t		j;
	size_t		i;

	i = index;
	tmp = NULL;
	while (line[i] == '$')
		i++;
	j = i;
	while (line[j] != '\0' && !is_quotes(line[j]) && line[j] != '$'
		&& !is_wspace(line[j]))
			j++;
	tmp = safe_malloc(sizeof(char) * (j + 1));
	if (!tmp)
		return (NULL);
	j = 0;
	while (line[i] != '\0' && line[i] != '\"' && line[i] != '\''
		&& line[i] != '$' && !is_wspace(line[i]))
			tmp[j++] = line[i++];
	tmp[j] = '\0';
	if (line[i] == '\0')
		i++;
	return (tmp);
}

/*-------------------------------------------------------------
moves past the dollar so variable becomes searchable (PATH)
compares with env list
if exp is empty because there is no match then it should be an empty
string ($PATHaaaa)
calls the switch
---------------------------------------------------------------*/
char	*get_expanded_hd(char **env, char *line, size_t index)
{
	char	*exp;
	char	*key;
	char	*tmp;

	tmp = NULL;
	exp = NULL;
	key = NULL;
	key = get_key_hd(line, index);
	if (!key)
		return (NULL);
	while (*key == '$')
		key++;
	exp = compare_with_env(key, env, exp);
	if (!exp)
		return (free(key), NULL);
	tmp = switcheroo_hd(line, exp, index);
	if (!tmp)
		return (free(key), NULL);
	if (key)
	{
		free (key);
		key = NULL;
	}
	return (tmp);
}

/*-------------------------------------------------------------
Expansion for heredoc
For example: >hello $USER -> hello maustel
---------------------------------------------------------------*/
char	*heredoc_expansion(char *line, char **env)
{
	size_t	index;
	char	*new_line;

	new_line = NULL;
	index = 0;
	while (line[index])
	{
		if (line[index] == '$' && ft_isalnum(line[index + 1]))
		{
			new_line = get_expanded_hd(env, line, index);
			if (!new_line)
				return (NULL);
		}
		index++;
	}
	if (new_line)
		return (new_line);
	return (line);
}
