/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_shell_ws.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:42:31 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/02 17:29:37 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_eichhoernchen.h"

void handle_quotes(t_shell *trim, char *input)
{
	char quote;

	if (trim->j > 0 && (!is_wspace(trim->res[trim->j - 1]))) // if not the beginning of res and the prior space is not ws
		trim->res[trim->j++] = ' ';
	quote = input[trim->i];
	trim->res[trim->j++] = input[trim->i++];
	while ((input[trim->i] != '\0') && (input[trim->i] != quote))
		trim->res[trim->j++] = input[trim->i++];
	if (input[trim->i] == quote)
	{
		trim->res[trim->j++] = input[trim->i];
		if (input[trim->i + 1] != '\0')
			trim->res[trim->j++] = ' ';
	}
	else
		printf("error\n"); // update here
}

void	handle_op(t_shell *trim, char *input)
{
	if (trim->j > 0 && (!is_wspace(trim->res[trim->j - 1]))) // if not the beginning of res and the prior space is not ws
		trim->res[(trim->j)++] = ' '; // insert ws if there is none
	trim->res[(trim->j)++] = input[trim->i]; // copying operator (not increasing i because of increase in function calling)
	if ((input[trim->i] == '<' && input[trim->i + 1] == '<') || (input[trim->i] == '>' && input[trim->i + 1] == '>'))
	{
		trim->res[trim->j++] = input[trim->i + 1]; //copy both operators
		if (input[trim->i + 2] != '\0')
			trim->res[trim->j++] = ' ';
		trim->i++;
		return ;
	}
	if (input[trim->i] != '$' && input[trim->i + 1] != '\0')
		trim->res[trim->j++] = ' ';
}

void	handle_special(t_shell *trim, char *input)
{
	char tmp;

	if ((input[trim->i] == '\'') || (input[trim->i] == '\"'))
		{
			handle_quotes(trim, input);
			trim->isspace = true;
		}
	else if (input[trim->i] == '|' || input[trim->i] == '>' || input[trim->i] == '<' || input[trim->i] == '$')
		{
			tmp = input[trim->i];
			handle_op(trim, input);
			if (tmp == '$')
				trim->isspace = false;
			else
				trim->isspace = true;
		}
}

void	populate_trim_str(t_shell *trim, char *input)
{
	trim->j = 0;
	trim->i = 0;
	trim->isspace = false; //flag to false
	while (trim->j < trim->len) // fixed wrong iterater in populate_trim_str
	{
		// printf("[%zu] < [%zu]\n", trim->j, trim->len);
		if (is_special(input[trim->i]))
			handle_special(trim, input);
		else if (is_wspace(input[trim->i])) // checks if there is a ws in input and sets it to one ws
		{
			if (!trim->isspace && trim->j > 0) // checks if isspace is false
			{
				trim->res[trim->j++] = ' '; // inserts space
				trim->isspace = true; // sets flag to true
			}
		}
		else
		{
			trim->res[trim->j++] = input[trim->i];
			trim->isspace = false;
		}
		// printf("str: {%s}\n", trim->res);
		trim->i++;
	}
	trim->res[trim->j] = '\0';
}


char *trim_spaces(char *input)
{
	t_shell	trim;
	char	*trim_inpt;

	if (!input)
		return (NULL);
	trim.res = NULL;
	trim_inpt = ft_strtrim(input, " \n\t");
	// trim.len = ft_strlen(trim_inpt); // calculate len properly?
	trim.len = get_len(trim_inpt);
	// trim.res = ft_calloc(sizeof(char), (trim.len + 1));
	trim.res = ft_calloc(sizeof(char), (trim.len + 1));
	if (!trim.res)
		return (NULL);
	populate_trim_str(&trim, trim_inpt);
	printf("\nonly edge trimmed string: [%s]\n", trim_inpt);
	printf("calculated length: %zu\n\n", trim.len);
	printf("trim.res: [%s]\n", trim.res);
	printf("actual result string length: %zu\n", ft_strlen(trim.res));
	free(trim_inpt);
	exit(EXIT_SUCCESS); /* for debugging */
	return (trim.res);
}

int	main()
{
	char	*input;
	char	*trim_inpt;
	char	*res;
	char	**tokens = NULL;
	t_list	*list = NULL;

	input = readline("Type Shit: ");
	if(!input)
		return (1);

	trim_inpt = trim_spaces(input);
	res = ft_strtrim(trim_inpt, " \n\t");

	tokens = split_space_quotes(res);

	list = tokeniser(tokens);

	// printf("\033[32mTOKEN LINKED LIST\n");
	// print_token_list(list);
	// printf("\033[0m");
	syntax_errors(list);

	parser(list);
	free(input);
	free(trim_inpt);
	free(res);
	ft_lstclear(&list, free_token);
	return (0);
}


// to do here
// 		create a function that correctly counts the len of the trimmed string


//       ls    -la| "        hello" > outfile >> out |        wc -l > $?
//    echo    $PATH   |grep "   : "| wc -l >      out>> outfile     > main
//
//ls    -la| "        hello" > outfile >> out |        wc -l > $?

// hello >shiti       >         fuck >>>   this
//

// ksdjasfüjaspodka | >> ||| <<<>>>><<< "ajsdjaslkdj " > jashd <<>> $$ $?<><<|" I love quotes'    '"' lalalal'
// -> correct

// "   hello   "<><<<<||shiti'fuck that    'plasegiveme|the<<>><<<>>>>>correct size    '"'$PATH$"$"''
// --> fiexed 

