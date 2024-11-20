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
	// printf(BLUE"len up to k: %zu\n"WHITE, len);
	while (line[j] == '$')
		j++;
	// printf(BLUE"len after $ skip: %zu\n"WHITE, len);
	while(line[j] != '\0' && !is_quotes(line[j]) && line[j] != '$' && !is_wspace(line[j]))
		j++;
	// printf(BLUE"len after variale name skip: %zu\n"WHITE, len);
	while(line[j] != '\0')
	{
		j++;
		len++;
	}
	// printf(BLUE"len with remainder: %zu\n"WHITE, len);
	len += ft_strlen(exp);
	// printf(BLUE"len with exp: %zu\n"WHITE, len);
	return (len);
}

char	*copy_into_tmp_hd(char *line, char *exp, size_t index, char *tmp, size_t len)
{
	size_t	iterate;
	size_t		j;
	int			i;

	j = 0;
	iterate = 0;
	i = 0;
	while(j < index)
		tmp[iterate++] = line[j++];
	j++;
	while(line[j] != '\0' && line[j] != '$' && !is_quotes(line[j]) && !is_wspace(line[j]))
		j++;
	while (exp[i] != '\0')
		tmp[iterate++] = exp[i++];
	if (exp)
		free(exp);
	// index = iterate;
	while (iterate < len)
	{
		tmp[iterate] = line[j];
		iterate++;
		j++;
	}
	tmp[iterate] = '\0';
	return (tmp);
}

int	switcheroo_hd(char *line, char *exp, size_t index)
{
	char		*tmp;
	size_t		len;

	len = get_len_exp_hd(line, exp, index);
	printf(GREEN"len: %ld\n"WHITE, len);
	tmp = safe_ft_calloc(len + 1, sizeof(char)); // tmp is allocated
	if (!tmp)
		return (-1);
	tmp = copy_into_tmp_hd(line, exp, index, tmp, len); // exp is freed
	printf(GREEN"line: %s\n"WHITE, line);
	if (line)
	{
		free(line);
		line = NULL;
	}
	printf(GREEN"tmp: %s\n"WHITE, tmp);
	line = safe_ft_strdup(tmp);
	if (!line)
		return (free(tmp), -1);
	printf(GREEN"line: %s\n"WHITE, line);
	if (tmp) // tmp is freed
		free(tmp);
	return (0);
}

/*-------------------------------------------------------------
tmp_dolalr
creates a searchable variable name to compare to the env variable list
i copies the position of index this is necessary so that
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
	while (line[i] == '$' /* || */ /* is_wspace(line[i]) */) // need to handle when there are chars before the variable in the quote
		i++;
	j = i;
	while (line[j] != '\0' && !is_quotes(line[j]) && line[j] != '$' && !is_wspace(line[j]))
		j++;
	tmp = safe_malloc(sizeof(char) * (j + 1));
	if (!tmp)
		return (NULL);
	j = 0;
	while (line[i] != '\0' && line[i] != '\"' && line[i] != '\'' && line[i] != '$' && !is_wspace(line[i]))
		tmp[j++] = line[i++];
	tmp[j] = '\0';
	if (line[i] == '\0')
		i++;
	// printf(GREEN"tmp: %s\n"WHITE, tmp);
	// printf(GREEN"len tmp: %zu\n"WHITE, ft_strlen(tmp));
	return (tmp);
}

/*-------------------------------------------------------------
moves past the dollar so variable becomes searchable (PATH)
compares with env list
if exp is empty because there is no match then it should be an empty string ($PATHaaaa)
calls the switch
---------------------------------------------------------------*/
int	get_expanded_hd(char *tmp, char **env, char *line, size_t index)
{
	char	*exp;
	char	*key;

	exp = NULL;
	key = NULL;
	key = get_key_hd(line, index); // key is allocated
	if (!key)
		return (-1);
	while (*key == '$')
		key++;
	exp = compare_with_env(key, env, exp); // exp is allocated
	if (!exp)
		return (free(key), -1);
	// printf(GREEN"exp: %s\n"WHITE, exp);
	if (switcheroo_hd(line, exp, index) == -1)
		return (free(key), -1);
	if (key)
	{
		free (key);
		key = NULL;
	}
	(void) tmp; //kann weg?
	return (0);
}



int	heredoc_expansion(char *line, char **env)
{
	size_t	index;
	char	*tmp;

	tmp = NULL;
	index = 0;
	while (line[index])
	{
		if (line[index] == '$' && ft_isalnum(line[index + 1]))
		{
			if (get_expanded_hd(tmp, env, line, index) == -1)
				return (-1);
		}
		index++;
	}
	return (0);
}
