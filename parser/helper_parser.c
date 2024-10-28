/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:04:44 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/10 16:28:18 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_eichhoernchen.h"

int	is_redirection(t_token *current_token)
{
	if (current_token->type == TOKEN_REDIN || current_token->type == TOKEN_REDOUT
		|| current_token->type == TOKEN_REDAPPEND || current_token->type == TOKEN_HEREDOC)
		return (1);
	else
		return (0);
}

int	is_filename(t_token *current_token)
{
	if (current_token->type == TOKEN_WORD || current_token->type == TOKEN_SQUOTES
		|| current_token->type == TOKEN_DQUOTES || current_token->type == TOKEN_ARGS
			|| current_token->type == TOKEN_EXITSTATUS)
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
