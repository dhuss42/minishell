/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:41:16 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/22 15:59:42 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_eichhoernchen.h"

int	double_quotes(t_command *row, t_shell *expand, char **env)
{
	char	*tmp;

	tmp = NULL;
	expand->quote = row->args[expand->i][expand->k];
	expand->k++;
	while (row->args[expand->i][expand->k] != expand->quote && row->args[expand->i][expand->k] != '\0')
	{
		// printf(BLUE"[%zu]current char in double quotes %c\n"WHITE, expand->k, row->args[expand->i][expand->k]);
		if (row->args[expand->i][expand->k] == '$' && ft_isalnum(row->args[expand->i][expand->k + 1]))
		{
			if (get_expanded(tmp, env, row, expand) == -1)
				return (-1);
		}
		else if (row->args[expand->i][expand->k] == '$' && (row->args[expand->i][expand->k + 1] == '?'))
		{
			if (get_exit_code(tmp, row, expand) == -1)
				return (-1);
		}
		else
			expand->k++;
	}
	if (row->args[expand->i][expand->k] == '\"')
		expand->k++;
	return (0);
}

// here
// sets quote to the current quote symbol in the og string
// iterates through the string until it reaches the end or the matching closing quote

void	skip_single_quotes(t_command *row, t_shell *expand)
{
	if (row->args[expand->i][expand->k] == '\'')
	{
		// printf(YELLOW"[%zu] opening quote %c\n", expand->k, row->args[expand->i][expand->k]);
		expand->k++;
	}
	while (row->args[expand->i][expand->k] != '\'' && row->args[expand->i][expand->k] != '\0')
	{
		// printf(GREEN"[%zu] between quotes %c\n", expand->k, row->args[expand->i][expand->k]);
		expand->k++;
	}
	if (row->args[expand->i][expand->k] == '\'')
	{
		// printf(YELLOW"[%zu] closing quote %c\n", expand->k, row->args[expand->i][expand->k]);
		expand->k++;
	}
}

int	check_for_expansion(t_command *row, t_shell *expand, char **env)
{
	char	*tmp;

	expand->k = 0;
	expand->quote = '\0';
	tmp = NULL;
	while (row->args[expand->i][expand->k] != '\0')
	{
		if (row->args[expand->i][expand->k] == '\"' && contains_dollar(row->args[expand->i], expand->k))
		{
			printf(RED"double quotes {%c} at [%zu]\n"WHITE, row->args[expand->i][expand->k], expand->k);
			if (double_quotes(row, expand, env) == -1)
				return (-1);
		}
		else if (row->args[expand->i][expand->k] == '\'')
		{
			printf(RED"single quotes {%c} at [%zu]\n"WHITE, row->args[expand->i][expand->k], expand->k);
			skip_single_quotes(row, expand);
		}
		else if (row->args[expand->i][expand->k] == '$' && ft_isalnum(row->args[expand->i][expand->k + 1]))
		{
			printf(RED"dollar {%c} at [%zu]\n"WHITE,row->args[expand->i][expand->k], expand->k);
			if (get_expanded(tmp, env, row, expand) == -1)
				return (-1);
		}
		else if (row->args[expand->i][expand->k] == '$' && (row->args[expand->i][expand->k + 1] == '?'))
		{
			printf(RED"EXIT CODE {%c} at [%zu]\n"WHITE,row->args[expand->i][expand->k], expand->k);
			if (get_exit_code(tmp, row, expand) == -1)
				return (-1);
		}
		else
		{
			printf(RED"ordinary char {%c} at [%zu]\n"WHITE,row->args[expand->i][expand->k], expand->k);
			expand->k++;
		}
		// printf(MAGENTA"current args[%zu]: %s\n", expand->i, row->args[expand->i]);
	}
	return (0);
}

// check for expansion
// goes through the single string
// 1. checks if the current position of the string is a double quote and if the string still contains dollars
// if yes it goes into double_quotes with "
// 2. checks if the current position of the string is a single quote and if it should expand (nbr of consequetive double_quotes % 2)
// if yes it goes into double_quotes with '
// 3. is the case where single double_quotes should not expand
// if this is true then it skipps all the chars until the closing quote
// 4. checks for $
// if yes it goes into tmp_dollar (creates searchable variable name) and get_expanded (gets the expansion)
// 5. moves the string index if nothing is the case

int	iterate_table(t_list *table, char **env)
{
	t_shell		expand;
	t_command	*row;

	expand.tmp = table;
	while (expand.tmp != NULL)
	{
		row = (t_command*)expand.tmp->content;
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
// --> works /////////
//"$PATH$HOME$a"
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
// --> works
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
//"!   $USER"
//"$USER    !"
//"!   $USER !"


// --- single double_quotes --- //
//'$PATH'
//'$PATH''$HOME'
//!!'$HOME'!!'$PATH'!!
//'$$PATH'
//'$PATH$'
//'$PATH$HOME$'
//'$PATH$HOME$a'
//'$PATH$HOME$$?'
//'$?$PATH$$$HOME$?'
//'$$$PATH$$$HOME$$'
//'PATH'
//'$'
//'aaaaa$PATH'
//'$PATHaaaaa'
//'$PATHaaaaa' '$HOME'
// '$PATHaaaaa' '$HOME'
// ''$HOME''
// '''$HOME'''
// '$PATH'''$HOME''
// ''$PATH'''$HOME'
// '$PATH'''$HOME'''''$SHLVL'''

//-- combi --//

// "'$PATH'"
// '"$PATH"'
// '$PATH'"$HOME"$SHLVL
// --> valgrind 3 errors in 3 contexts
// "'$PATH'"$HOME"$SHLVL"
// ''$PATH'"$HOME"$SHLVL'
// ''$PATH''"$HOME"
// "'"$SHLVL'"'
// echo ""$SHLVL""'$PATH"$HOME  "$PATH'
// $USER'''"$PWD  $SHELL"'"     ls" |'   $LOGNAME'

// need more tests

//-- envs --//
// $LOGNAME
// $OLDPWD
// $USER
// $SHELL
// $PWD


//--- tests that do not work --- /
// "   $USER "
// --> space after variable is counted as part of the variable
// --- solved ---- //

// '$PATH"$HOME"$SHLVL'$USER'""'"$PWD"'"$LOGNAME .            babababababababab"'
// '$PATH"$HOME"$SHLVL' $USER '""' "$PWD" '"$LOGNAME .            babababababababab"'
// --> issue with expanding "$LOGNAME"
// '""'"$PWD"'"$LOGNAME .            babababababababab"'
// --> splitting process is not working correctly here
// --> '""' "$PWD" '"$LOGNAME .            babababababababab"'
// --> not a problem in get_len lexer and insert ws lexer
// --> might be an issue in the splitting process

// more tests //
//echo "This is a test" | tr '[:lower:]' '[:upper:]' > output.txt
//cat input.txt | grep -E "error|warning" | awk '{print $1}' | sort | uniq > results.log
//VAR1="Hello"; VAR2="World"; echo "$VAR1, $VAR2!" >> greetings.txt
//cat data.csv | awk -F',' '{print $2}' | grep "active" | wc -l > active_users.txt
//echo 'My name is "John Doe"' | sed 's/John/Jane/' | tee result.txt | grep "Jane"
//find . -type f -name "*.sh" | xargs grep "TODO" | tee todos.txt | wc -l
//ls -lh | grep -v "total" | awk '{print $9}' | while read file; do echo "File: $file"; done
//echo 'He said, "It\'s time."' | tr ' ' '\n' | sort | uniq -c
//cat <<EOF > testfile.txt
//echo "Variable assignment test" && VAR="This is a test" && echo $VAR > var_test.txt
//diff <(ls -l /dir1) <(ls -l /dir2) | grep "^<" | wc -l
//echo 'Result of 2 + 2 is:' $(expr 2 + 2) | tee math_result.txt
//echo "The user's home directory is: $HOME" | sed 's/home/house/'
//cat 'single_file.txt' | grep "pattern" | awk '{print $3 " " $1}' | sort -r | tee sorted_output.txt
//cat <<'EOF' | sed 's/foo/bar/g' > replaced.txt


//echo "$HOME""'  shit $SHLVL   "'$PATH  '''$PATH"''" | $SHLVL$USER$SHLVL | "" '"' "'" '"' "'" '"' "" "" "" "" "''''''''''$HOME'"
