/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_trim_ws.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:42:31 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/02 17:29:37 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_special(char input)
{
	char *special;

	special = "<>|\'\"$";
	while (*special != '\0')
	{
		if (input == *special)
			return (true);
		special++;
	}
	return (false);
}

bool	is_wspace(char input)
{
	char	*ws;

	ws = "\n\t ";
	while (*ws != '\0')
	{
		if (input == *ws)
			return (true);
		ws++;
	}
	return (false);
}

void handle_quotes(t_trim *trim, char *input)
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
			trim->res[trim->j++] = ' ';
	}
	else
		printf("error\n"); // update here
}

void	handle_op(t_trim *trim, char *input)
{
	if (trim->j > 0 && (!is_wspace(trim->res[trim->j - 1]))) // if not the beginning of res and the prior space is not ws
		trim->res[(trim->j)++] = ' '; // insert ws if there is none
	trim->res[(trim->j)++] = input[trim->i]; // copying operator (not increasing i because of increase in function calling)
	if ((input[trim->i] == '<' && input[trim->i + 1] == '<') || (input[trim->i] == '>' && input[trim->i + 1] == '>'))
	{
		trim->res[trim->j++] = input[trim->i + 1]; //copy both operators
		trim->res[trim->j++] = ' ';
		trim->i++;
		return ;
	}
	if (input[trim->i] != '$')
		trim->res[trim->j++] = ' ';
}

void	handle_special(t_trim *trim, char *input)
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

void	populate_trim_str(t_trim *trim, char *input)
{
	trim->j = 0;
	trim->i = 0;
	trim->isspace = false; //flag to false
	while (trim->i < trim->len)
	{
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
		trim->i++;
	}
	trim->res[trim->j] = '\0';
}

char *trim_spaces(char *input)
{
	t_trim	trim;
	char	*trim_inpt;

	if (!input)
		return (NULL);
	trim.res = NULL;
	trim_inpt = ft_strtrim(input, " \n\t");
	trim.len = ft_strlen(trim_inpt); // calculate len properly?

	// trim.res = ft_calloc(sizeof(char), (trim.len + 1));
	trim.res = ft_calloc(sizeof(char), (7000 + 1));
	if (!trim.res)
		return (NULL);
	populate_trim_str(&trim, trim_inpt);
	free(trim_inpt);
	return (trim.res);
}

int	main()
{
	char	*input;
	char	*trim_inpt;
	char	*res;
	char	**tokens = NULL;
	t_list	*list = NULL;
	// int		i = 0;

	input = readline("Type Shit: ");
	if(!input)
		return (1);

	trim_inpt = trim_spaces(input);
	res = ft_strtrim(trim_inpt, " \n\t");

	tokens = split_space_quotes(res);

	list = tokeniser(tokens);

	printf("\033[32mTOKEN LINKED LIST\n");
	print_token_list(list);
	printf("\033[0m");
	free(input);
	free(trim_inpt);
	free(res);
	ft_lstclear(&list, free_token);
	return (0);
}


//        HELLO << this isa$PATH"CHECK .   JESUS" . halleluija | <>>>'shiti '