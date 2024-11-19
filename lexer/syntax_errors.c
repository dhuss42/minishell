/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:59:03 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/19 12:11:11 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			print_error(258, next_token->input, PRINT);
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
		print_error(258, "newline", PRINT);
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
		print_error(258, "|", PRINT);
		return (true);
	}
	if (next_token->type == TOKEN_PIPE)
	{
		print_error(258, "|", PRINT);
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
		print_error(258, "|", PRINT);
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

// random segmentation fault when typing: |
