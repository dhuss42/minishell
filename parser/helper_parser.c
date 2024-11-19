/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:04:44 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/19 12:11:40 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redirection(t_token *current_token)
{
	t_token_type	tokt;

	tokt = current_token->type;
	if (tokt == TOKEN_REDIN || tokt == TOKEN_REDOUT || tokt == TOKEN_REDAPPEND
		|| tokt == TOKEN_HEREDOC)
		return (1);
	else
		return (0);
}

int	is_filename(t_token *current_token)
{
	t_token_type	tokt;

	tokt = current_token->type;
	if (tokt == TOKEN_WORD || tokt == TOKEN_SQUOTES || tokt == TOKEN_DQUOTES
		|| tokt == TOKEN_ARGS || tokt == TOKEN_EXITSTATUS)
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
