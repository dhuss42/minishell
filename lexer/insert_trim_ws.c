/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_trim_ws.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:42:31 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/27 15:28:13 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_quotes(t_shell *trim, char *input)
{
	char	quote;

	quote = input[trim->i];
	trim->res[trim->j++] = input[trim->i++];
	while ((input[trim->i] != '\0') && (input[trim->i] != quote))
		trim->res[trim->j++] = input[trim->i++];
	if (input[trim->i] == quote)
	{
		trim->res[trim->j++] = input[trim->i];
	}
}

// for proper quote handling remove ws insertion before and after the quotes

void	handle_op(t_shell *trim, char *input)
{
	if (trim->j > 0 && (!is_wspace(trim->res[trim->j - 1])))
		trim->res[(trim->j)++] = ' ';
	trim->res[(trim->j)++] = input[trim->i];
	if ((input[trim->i] == '<' && input[trim->i + 1] == '<')
		|| (input[trim->i] == '>' && input[trim->i + 1] == '>'))
	{
		trim->res[trim->j++] = input[trim->i + 1];
		if (input[trim->i + 2] != '\0')
			trim->res[trim->j++] = ' ';
		trim->i++;
		return ;
	}
	if (input[trim->i + 1] != '\0')
		trim->res[trim->j++] = ' ';
}

// if not the beginning of res and the prior space is not ws
// insert ws if there is none
// copying operator (not increasing i because of increase in function calling)
//copy both operators

void	handle_special(t_shell *trim, char *input)
{
	if ((input[trim->i] == '\'') || (input[trim->i] == '\"'))
	{
		handle_quotes(trim, input);
		trim->isspace = false;
	}
	else if (input[trim->i] == '|' || input[trim->i] == '>'
		|| input[trim->i] == '<')
	{
		handle_op(trim, input);
		trim->isspace = true;
	}
}

void	populate_trim_str(t_shell *trim, char *input)
{
	trim->j = 0;
	trim->i = 0;
	trim->isspace = false;
	while (trim->j < trim->len)
	{
		if (is_special(input[trim->i]))
			handle_special(trim, input);
		else if (is_wspace(input[trim->i]))
		{
			if (!trim->isspace && trim->j > 0)
			{
				trim->res[trim->j++] = ' ';
				trim->isspace = true;
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

// checks if there is a ws in input and sets it to one ws
// checks if isspace is false
// inserts space

char	*trim_spaces(char *input, t_shell *shell)
{
	t_shell	trim;
	char	*trim_inpt;

	trim.res = NULL;
	trim_inpt = ft_strtrim(input, " \n\t");
	if (!trim_inpt)
	{
		print_error(errno, NULL, PRINT);
		return (NULL);
	}
	trim.len = get_len(trim_inpt, shell);
	if (shell->syntax_error == true)
		return (free(trim_inpt), NULL);
	trim.res = ft_calloc(sizeof(char), (trim.len + 1));
	if (!trim.res)
	{
		print_error(errno, NULL, PRINT);
		return (free(trim_inpt), NULL);
	}
	populate_trim_str(&trim, trim_inpt);
	if (trim_inpt)
		free(trim_inpt);
	return (trim.res);
}
