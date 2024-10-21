/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:41:16 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/21 16:19:27 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_eichhoernchen.h"

bool	is_quotes(char c)
{
	if (c == '\'')
		return (true);
	if (c == '\"')
		return (true);
	return (false);
}

char	*tmp_dollar(t_command *row, t_shell *expand)
{
	char	*tmp;

	tmp = NULL;
	while (row->args[expand->i][expand->k] == '$')
		expand->k++;
	expand->j = expand->k;
	while (row->args[expand->i][expand->j] != '\0' && !is_quotes(row->args[expand->i][expand->j]) && row->args[expand->i][expand->j] != '$') // getting len
		expand->j++;
	tmp = malloc(sizeof(char) * (expand->j + 1));
	if (!tmp)
		return (NULL);
	expand->j = 0;
	while (row->args[expand->i][expand->k] != '\0' && row->args[expand->i][expand->k] != '\"' && row->args[expand->i][expand->k] != '\'' && row->args[expand->i][expand->k] != '$')
		tmp[expand->j++] = row->args[expand->i][expand->k++];
	tmp[expand->j] = '\0';
	if (row->args[expand->i][expand->k] == expand->quote)
		expand->k++;
	printf("tmp_dollar: %s\n", tmp);
	return (tmp);
}

// tmp_dolalr
// creates a searchable variable name to compare to the env variable list
// skipps adjancent $ ($$PATH)
// gets the length of the string ($PATH)
// allocates the tmp string
// copies into tmp (boraders are " ' $ ($PATH$) and \0)
// moves og string past closing quote if there is one

bool	contains_dollar(char *str, size_t i)
{
	// i++;
	while (str[i] != '\0' /* && str[i] != '\"' */)
	{
		if (str[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

void	check_for_expansion(t_command *row, t_shell *expand, char **env)
{
	char	*tmp;

	expand->k = 0;
	tmp = NULL;
	while (row->args[expand->i][expand->k] != '\0') // going through string
	{
		printf(CYAN"{{%zu}}\n"WHITE, expand->k);
		printf("row->args[*i]: %s\n", row->args[expand->i]);
		printf("current char: %c \n", row->args[expand->i][expand->k]);
		if (row->args[expand->i][expand->k] == '\"' && contains_dollar(row->args[expand->i], expand->k))
		{
			printf(RED"DOUBLEQUOTES\n"WHITE);
			quotes(row, expand, env);
		}
		else if (row->args[expand->i][expand->k] == '\'' && contains_dollar(row->args[expand->i], expand->k) && should_expand(row->args[expand->i], expand->k))
		{
				printf(RED"SINGLEQUOTES\n"WHITE);
				quotes(row, expand, env);
		}
		else if (row->args[expand->i][expand->k] == '\'' && contains_dollar(row->args[expand->i], expand->k) && !should_expand(row->args[expand->i], expand->k)) // skipping '''$HOME'''
		{
			if (row->args[expand->i][expand->k] == '\'')
			{
				printf(YELLOW"[%zu]current char quote: %c\n"WHITE, expand->k, row->args[expand->i][expand->k]);
				expand->k++;
			}
			while (row->args[expand->i][expand->k] != '\'' && row->args[expand->i][expand->k] != '\0')
			{
				printf(GREEN"[%zu]current char in loop: %c\n"WHITE, expand->k, row->args[expand->i][expand->k]);
				expand->k++;
			}
			if (row->args[expand->i][expand->k] == '\'')
			{
				printf(YELLOW"[%zu]current char quote: %c\n"WHITE, expand->k, row->args[expand->i][expand->k]);
				expand->k++;
			}
		}
		else if (row->args[expand->i][expand->k] == '$')
		{
			printf(RED"$\n"WHITE);
			tmp = tmp_dollar(row, expand);
			get_expanded(tmp, env, row, expand);
		}
		else
		{
			printf("TEST20\n");
			expand->k++;
		}
	}
}

// check for expansion
// goes through the single string
// 1. checks if the current position of the string is a double quote and if the string still contains dollars
// if yes it goes into quotes with "
// 2. checks if the current position of the string is a single quote and if it should expand (nbr of consequetive quotes % 2)
// if yes it goes into quotes with '
// 3. is the case where single quotes should not expand
// if this is true then it skipps all the chars until the closing quote
// 4. checks for $
// if yes it goes into tmp_dollar (creates searchable variable name) and get_expanded (gets the expansion)
// 5. moves the string index if nothing is the case

bool	iterate_table(t_list *table, char **env)
{
	t_shell		expand;
	t_command	*row;

	expand.tmp = table;
	while (expand.tmp != NULL) // going trough table row for row
	{
		row = (t_command*)expand.tmp->content;
		expand.i = 0;
		while (row->args[expand.i] != NULL) // going through double char args
		{
			printf(RED"{%zu}\n"WHITE, expand.i);
			check_for_expansion(row, &expand, env);
			expand.i++;
		}
		expand.tmp = expand.tmp->next;
	}
	return (true); // change
}

// function iterates through the table and the double char
// for every line it checks possible expansions




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
// --> does not work
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

// "'$PATH'"
// --> problem: pos_dollar: PATH'
// need to change expansion -> quotes to check if " or '