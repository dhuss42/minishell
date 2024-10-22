/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switcheroo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:41:27 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/21 16:27:09 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell_eichhoernchen.h"

size_t	strlen_equal(char *str)
{
	size_t  i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	return (i);
}

char	*compare_with_env(char *variable, char **env, char *exp)
{

	size_t  j = 0;

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
	printf(GREEN"[%zu] current char at index k: %c\n"WHITE, expand->k, row->args[expand->i][expand->k]);
	while(/* row->args[expand->i][j] != '\0' && !(row->args[expand->i][j] == '$' && ft_isalnum(row->args[expand->i][j + 1])) */ j < expand->k) // getting len up to first dollar
	{
		len++;
		j++;
	}
	while (row->args[expand->i][j] == '$')
		j++;
	while(row->args[expand->i][j] != '\0' && row->args[expand->i][j] != expand->quote && row->args[expand->i][j] != '$') // skipping until closing quote or dollar
		j++;
	while(row->args[expand->i][j] != '\0') // getting len of remainder
	{
		j++;
		len++;
	}
	len += ft_strlen(exp);
	return (len);
}

// gets the length up until the first dollar sign (aaaa$HOME) --> this could be an issue it should get the length up until the index of the first dollar sign
// skipps adjacent $ (aa$$HOME)
// skipps until closing quote or $ sign ($HOME$)
// gets the len of the remainder of the string ($HOME$a)
// adds the length of the expanded string

void	switcheroo(t_command *row, char *exp, t_shell *expand)
{
	size_t  len;
	size_t  iterate;
	size_t  index;
	char	*tmp;

	expand->j = 0;
	iterate = 0;
	index = 0;

	len = get_len_exp(row, exp, expand);
	tmp = ft_calloc(len + 1, sizeof(char));
	if (!tmp)
		return ;
	printf(YELLOW"[%zu]1. current char quote: %c\n"WHITE, expand->j, row->args[expand->i][expand->j]);
	while(/* row->args[expand->i][expand->j] != '\0' && !(row->args[expand->i][expand->j] == '$' && ft_isalnum(row->args[expand->i][expand->j + 1])) */expand->j < expand->k)
	{
		tmp[iterate++] = row->args[expand->i][expand->j++];
		printf(MAGENTA"[%zu]current char quote in loop: %c\n"WHITE, expand->j, row->args[expand->i][expand->j]);
	}
	expand->j++;
	printf(YELLOW"[%zu]2. current char quote: %c\n"WHITE, expand->j, row->args[expand->i][expand->j]);
	while(row->args[expand->i][expand->j] != '\0' && row->args[expand->i][expand->j] != '$' && !is_quotes(row->args[expand->i][expand->j]))
	{
		expand->j++;
		printf(BLUE"[%zu]current char quote in loop: %c\n"WHITE, expand->j, row->args[expand->i][expand->j]);
	}
	printf(YELLOW"[%zu]3. current char quote: %c\n"WHITE, expand->j, row->args[expand->i][expand->j]);
	while (exp[index] != '\0')
	{
		tmp[iterate++] = exp[index++];
		printf(MAGENTA"[%zu]current char quote in loop: %c\n"WHITE, expand->j, row->args[expand->i][expand->j]);
	}

	if (exp)
		free(exp);

	expand->k = iterate;

	while (row->args[expand->i][expand->j] != '\0')
	{
		printf(MAGENTA"[%zu]current char quote in loop: %c\n"WHITE, expand->k, row->args[expand->i][expand->k]);
		tmp[iterate++] = row->args[expand->i][expand->j++];
	}
	printf(YELLOW"[%zu]current char quote: %c\n"WHITE, expand->k, row->args[expand->i][expand->k]);
	tmp[iterate] = '\0';
	printf("tmp: %s\n", tmp);

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
	printf("finished switcheroo\n");
}

// switcheroo
// gets len of the complete expanded string
// allocates the tmp char in which the expanded string will be copied
// copies everything up until the first dollar sign into the tmp string --> this is where an issue could be, should copy up until expand->k maybe
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

	while (*variable == '$')
		variable++;
	exp = compare_with_env(variable, env, exp);
	if (!exp)
		exp = ft_strdup("");
	switcheroo(row, exp, expand);
}

// moves past the dollar so variable becomes searchable (PATH)
// compares with env list
// if exp is empty because there is no match then it should be an empty string ($PATHaaaa)
// calls the switch