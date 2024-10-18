/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:41:16 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/18 16:34:19 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "../minishell_eichhoernchen.h"


char	*tmp_dollar(t_command *row, size_t *i, size_t *k)
{
	size_t j;
	char	*tmp;

	printf("TEST3\n");
	tmp = NULL;
	printf("pos row->args[*i][*k]: %c\n", row->args[*i][*k]);
	while (row->args[*i][*k] == '$' || row->args[*i][*k] == '\"')
	{
		printf("in while pos row->args[*i][*k]: %c\n", row->args[*i][*k]);
		(*k)++;
	}
	j = *k;
	printf("in tmp_dollar row->args[*i]: %s\n", row->args[*i]);
	printf("pos row->args[*i][*k]: %c\n", row->args[*i][*k]);
	printf("len: %zu\n", ft_strlen(row->args[*i]));
	while (row->args[*i][j] != '\0' && row->args[*i][j] != '\"' && row->args[*i][j] != '$') // getting len
		j++;
	printf("TEST3.1\n");
	tmp = malloc(sizeof(char) * (j + 1));
	if (!tmp)
		return (NULL);
	j = 0;
	printf("TEST3.2\n");
	while (row->args[*i][*k] != '\0' && row->args[*i][*k] != '\"' && row->args[*i][*k] != '$')
		tmp[j++] = row->args[*i][(*k)++];
	tmp[j] = '\0';

	printf("TEST3.3\n");
	if (row->args[*i][*k] == '\"')
		(*k)++;
	printf("tmp_dollar: %s\n", tmp);
	// exit(EXIT_SUCCESS);
	return (tmp);
}

bool	contains_dollar(char *str, size_t i)
{
	i++;
	while (str[i] != '\0' && str[i] != '\"')
	{
		if (str[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

void	which_quotes(t_command *row, size_t *i, char **env)
{
	size_t  k;
	char	*tmp;

	k = 0;
	// size_t round = 0;
	tmp = NULL;
	printf("TEST2\n");
	while (row->args[*i][k] != '\0') // going through string
	{
		// printf("TEST21\n");
		printf("row->args[*i]: %s\n", row->args[*i]);
		printf("current char: %c \n", row->args[*i][k]);
		if (row->args[*i][k] == '\"' && contains_dollar(row->args[*i], k))
		{
			printf("IN HERE\n");
			k++;
			while (row->args[*i][k] != '\"' && row->args[*i][k] != '\0')
			{
				// while (row->args[*i][k] != '\0' && row->args[*i][k] != '$')
				// {
				// 	printf(MAGENTA"skipping leading $: %c \n"WHITE, (row->args[*i][k]));
				// 	k++;
				// }
				if (row->args[*i][k] == '\0')
					break ;
				// printf(MAGENTA"round [%zu]\n"WHITE, round++);
				// printf(MAGENTA"current char: %c \n"WHITE, (row->args[*i][k]));
				if (row->args[*i][k] == '$' && ft_isalnum(row->args[*i][k + 1]))
				{
					tmp = tmp_dollar(row, i, &k);
					// printf("tmp_dollar: {%s}\n", tmp);
					get_expanded_2(tmp, env, row, i, &k);
					// printf("after get_expanded row->args[*i]: %s\n", row->args[*i]);
					// printf("TEST18\n");
				}
				if (tmp)
				{
					// printf("TEST19\n");
					// printf(YELLOW"address tmp in which_quotes: %p\n"WHITE, tmp);
					free(tmp);
					// printf("TEST19.1\n");
					tmp = NULL;
				}
				// printf(MAGENTA"before end of loop current char: %c \n"WHITE, (row->args[*i][k]));
				if (!(row->args[*i][k] == '$' && ft_isalnum(row->args[*i][k + 1])))
					k++;
				// printf(MAGENTA"after end of loop current char: %c \n"WHITE, (row->args[*i][k]));
			}
		}
		else if (row->args[*i][k] == '\'' && contains_dollar(row->args[*i], k) && should_expand(row->args[*i], k))
		{
				printf(RED"SINGLEQUOTES\n"WHITE);
				k++;
		}
		else
		{
			printf("TEST20\n");
			k++;
		}
	}
}

// not checking for a dollar inside the quotes!! so exp is NULL when there is no dollar!

bool	check_for_quotes(t_list *table, char **env)
{
	t_list	  *tmp;
	t_command   *row;
	size_t	  i;

	tmp = table;
	while (tmp != NULL) // going trough table row for row
	{
		row = (t_command*)tmp->content;
		i = 0;
		while (row->args[i] != NULL) // going through double char args
		{
			// printf("TEST\n");
			which_quotes(row, &i, env);
			i++;
		}
		tmp = tmp->next;
	}
	return (true); // change
}



// ---- quote handling --- //
// char quotes
// go through the string and check if there are quotes
//	  if there are quotes save quote symbol
//	  find end of quote
//	  call expansion if " "; but only expand what is inside the quote
//		  call with $PATH if "$PATH"
//	  move on

// --- expansion inside quote ---- //
//
//	  get /usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/sbin
//	  copy current content of args until first occurance of $ + the passed content inside the quote (strncmp)
//	  replace first occurance of $ + the passed content inside the quote with /usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/sbin
//	  copy remaining string
//
// --- quote removal ---- //
// char quote
// get_len of string with quotes theoretically removed
// go through string and check for quotes
//	  copy into 2nd string
//	  if there is a quote save symbol
//		  don't copy quote symbol
//		  copy content between quotes up to closing
//		  don't copy closing quote


// ---- test cases ----- //
//"$PATH"
// --> beginning of quote is copied due to how the expansion handles chars before the dollar sign
// --> /-- solved --/
//"$PATH""$HOME"
// --> only $PATH is expanded
// -- > /-- solved --/
// !!"$HOME"!!"$PATH"!!
// --> issue at test14, test3, and test 19
// --> // -- solved get_len_exp was not counting total len -- //
//"$$PATH"
// --> issue
// --> idea might need to check next char for is_alnum
// --> /--- solved ----/
//"$PATH$"
// --> issue creates tmp_dollar PATH$ does not find matching env and returns nullterminated string
// --> /--- solved ----/
//"$PATH$HOME$"
// --> solved
//"$PATH$HOME$a"
// --> works
//"$PATH$HOME$$?"
// --> works
//"$PATH$HOME$$?"
// --> works
//"$?$PATH$$$HOME$?"
// --> works
//"$$$PATH$$$HOME$$"
// --> works
//"PATH"
// --> works
//"$"
// --> returns empty string
//"hallo"
// -->works
//"aaaaa$PATH"
// --> works
//"$PATHaaaaa"
// --> works (included ft_bzero when there is no matching env found)
// --> does not work because of ft?bzero remove
// --> setting exp to "" works
//"$PATHaaaaa" "$HOME"
// --> works bzero solved iterater problem where args[i] is NULL but the args[i + 1] contains a string
// --> does not work because of ft?bzero remove
// --> setting exp to "" works
// "$PATH$a$HOME"
// --> setting exp to "" works