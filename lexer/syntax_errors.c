/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:59:03 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/09 12:08:50 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_eichhoernchen.h"

void	syntax_error_red(t_list *tl_pos)
{
	t_list	*tmp;
	token	*next_token;

	tmp = tl_pos;
	if (tmp->next != NULL)
	{
		next_token = (token *)tmp->next->content;
		if (!is_filename(next_token))
		{
			printf("\033[31mSYYYNTAX ERROR! WRONG FILENAME\n\033[0m");
			exit(EXIT_FAILURE); // change
		}
		if (is_redirection(next_token) || next_token->type == TOKEN_PIPE)
		{
			printf("\033[31mSYYYNTAX ERROR! CONSECUTIVE REDIRECTION OR PIPE\n\033[0m");
			exit(EXIT_FAILURE); // change
		}
	}
	else if (tmp->next == NULL)
	{
		printf("\033[31mSYYYNTAX ERROR! NOTHING AFTER REDIRECTION\n\033[0m");
		exit(EXIT_FAILURE); // change
	}
}

void	syntax_error_pipe(t_list *tl_pos)
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
			printf("\033[31mSYYYNTAX ERROR! CONSECUTIVE PIPES\n\033[0m");
			exit(EXIT_FAILURE); // change
		}
	}
}

// commented out section concerns a missing cmd after the Pipe, bash waits for a cmd so not really a syntax error


void	syntax_errors(t_list *token_list)
{
	t_list	*tmp;
	token	*current_token;

	current_token = NULL;
	tmp = token_list;
	current_token = (token *)tmp->content;
	if (current_token->type == TOKEN_PIPE)
	{
		printf("\033[31mSYYYNTAX ERROR! NOTHING BEFORE PIPE\n\033[0m");
		exit(EXIT_FAILURE); // change
	}
	while (tmp != NULL)
	{
		current_token = (token *)tmp->content;
		if (is_redirection(current_token))
			syntax_error_red(tmp);
		else if (current_token->type == TOKEN_PIPE)
			syntax_error_pipe(tmp);
		tmp = tmp->next;
	}
}

// to do here
//	  change exit failure to something that stores the exit code in struct and procede accordingly
//	  test this in more detail