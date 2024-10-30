/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:59:03 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/10 11:45:17 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_eichhoernchen.h"

bool	syntax_error_red(t_list *tl_pos)
{
	t_list	*tmp;
	t_token	*next_token;

	tmp = tl_pos;
	if (tmp->next != NULL)
	{
		next_token = (t_token *)tmp->next->content;
		if (is_redirection(next_token) || next_token->type == TOKEN_PIPE)
		{
			// print_error(258, nex_token->input);
			printf("\033[31mminishell: syntax error near unexpected token `\033[0m");
			printf("%s'\n", next_token->input);
			return (true);
		}
/* 		if (!is_filename(next_token))
		{
			printf("\033[31mSYYYNTAX ERROR! WRONG FILENAME\n\033[0m");
			exit(EXIT_FAILURE); // change
		} */ // removed because wrong filename is not a syntax error
	}
	else if (tmp->next == NULL)
	{
		// print_error(258, `newline');
		printf("\033[31mminishell: syntax error near unexpected token `newline'\n\033[0m");
		return (true);
	}
	return (false);
}

bool	syntax_error_pipe(t_list *tl_pos)
{
	t_list	*tmp;
	t_token	*next_token;

	tmp = tl_pos;
	if (tmp->next != NULL)
		next_token = (t_token *)tmp->next->content;
	if (tmp->next == NULL)
	{
		// print_error(258, `|');
		printf("\033[31mminishell: syntax error near unexpected token `|'\n\033[0m");
		return (true);
	}
	if (next_token->type == TOKEN_PIPE)
	{
		// print_error(258, `|');
		printf("\033[31mminishell: syntax error near unexpected token `|'\n\033[0m");
		return (true);
	}
	return (false);
}

bool	syntax_errors(t_list *token_list)
{
	t_list	*tmp;
	t_token	*current_token;

	current_token = NULL;
	tmp = token_list;
	current_token = (t_token *)tmp->content;
	if (current_token->type == TOKEN_PIPE)
	{
		// print_error(258, "`|'");
		printf("\033[31mminishell: syntax error near unexpected token `|'\n\033[0m");
		return (true);
	}
	while (tmp != NULL)
	{
		current_token = (t_token *)tmp->content;
		if (is_redirection(current_token))
		{
			if (syntax_error_red(tmp) == true)
				return (true);
		}
		else if (current_token->type == TOKEN_PIPE)
		{
			if (syntax_error_pipe(tmp) == true)
				return (true);
		}
		tmp = tmp->next;
	}
	return (false);
}

// handle syntax errors properly
//	what gets set to print_error
//	stop the string from moving further in minishell loop
