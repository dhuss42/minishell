/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:04:44 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/27 12:57:42 by dhuss            ###   ########.fr       */
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

size_t	ft_strlcpy_lowercase(char *dst, const char *src, size_t dstsize)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (dstsize != '\0')
	{
		while (dstsize > 1 && src[i] != '\0')
		{
			dst[i] = ft_tolower(src[i]);
			i++;
			dstsize--;
		}
		dst[i] = '\0';
	}
	while (src[j] != '\0')
		j++;
	return (j);
}

