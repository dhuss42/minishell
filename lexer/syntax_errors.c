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
	token	*next_token;

	tmp = tl_pos;
	if (tmp->next != NULL)
	{
		next_token = (token *)tmp->next->content;
		if (is_redirection(next_token) || next_token->type == TOKEN_PIPE)
		{
			// print_error(258, NULL);
			printf("\033[31mSYYYNTAX ERROR! CONSECUTIVE REDIRECTION OR PIPE FOLLOWING REDIRECTION\n\033[0m");
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
		// print_error(258, NULL);
		printf("\033[31mSYYYNTAX ERROR! NOTHING AFTER REDIRECTION\n\033[0m");
		return (true); // change
	}
	return (false);
}

bool	syntax_error_pipe(t_list *tl_pos)
{
	t_list	*tmp;
	token	*next_token;

	tmp = tl_pos;
	if (tmp->next != NULL)
	{
		next_token = (token *)tmp->next->content;
	// if (tmp->next == NULL)
	//	 printf("SYYYNTAX ERROR! NOTHING AFTER PIPE\n");
		if (next_token->type == TOKEN_PIPE)
		{
			// print_error(258, NULL);
			// printf("\033[31mSYYYNTAX ERROR! CONSECUTIVE PIPES\n\033[0m");
			return (true); // change
		}
	}
	return (false);
}

// commented out section concerns a missing cmd after the Pipe, bash waits for a cmd so not really a syntax error


bool	syntax_errors(t_list *token_list)
{
	t_list	*tmp;
	token	*current_token;

	current_token = NULL;
	tmp = token_list;
	current_token = (token *)tmp->content;
	if (current_token->type == TOKEN_PIPE)
	{
		// print_error(258, NULL); custom_error for syntax
		printf("\033[31mSYYYNTAX ERROR! NOTHING BEFORE PIPE\n\033[0m");
		return (true);
	}
	while (tmp != NULL)
	{
		current_token = (token *)tmp->content;
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
