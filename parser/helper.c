/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:04:44 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/09 14:01:14 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_eichhoernchen.h"

int is_redirection(token *current_token)
{
	if (current_token->type == TOKEN_REDIN || current_token->type == TOKEN_REDOUT
		|| current_token->type == TOKEN_REDAPPEND || current_token->type == TOKEN_HEREDOC)
		return (1);
	else
		return (0);
}

int is_filename(token *current_token)
{
	if (current_token->type == TOKEN_WORD || current_token->type == TOKEN_SQUOTES
		|| current_token->type == TOKEN_DQUOTES || current_token->type == TOKEN_ARGS
			|| current_token->type == TOKEN_EXITSTATUS) // if you type > $? it creates a file with the last exit status
		return (1);
	else
		return (0);
}

void	set_to_zero(t_shell *nbr)
{
	nbr->words = 0;
	nbr->reds = 0;
	nbr->filenames = 0;
}
