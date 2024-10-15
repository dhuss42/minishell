/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:12:09 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/10 16:28:14 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_eichhoernchen.h"

bool	is_special(char input)
{
	char *special;

	special = "<>|\'\"";
	while (*special != '\0')
	{
		if (input == *special)
			return (true);
		special++;
	}
	return (false);
}

bool	is_special_no_quotes(char input)
{
	char *special;

	special = "<>|";
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
