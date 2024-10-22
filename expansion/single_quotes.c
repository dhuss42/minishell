/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:41:51 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/22 15:41:59 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_eichhoernchen.h"

void	quotes(t_command *row, t_shell *expand, char **env)
{
	char	*tmp;

	tmp = NULL;
	expand->quote = row->args[expand->i][expand->k];
	expand->k++;
	while (row->args[expand->i][expand->k] != expand->quote && row->args[expand->i][expand->k] != '\0')
	{
		if (row->args[expand->i][expand->k] == '$' && ft_isalnum(row->args[expand->i][expand->k + 1]))
			get_expanded(tmp, env, row, expand);
		else
			expand->k++;
	}
}

// here
// sets quote to the current quote symbol in the og string
// iterates through the string until it reaches the end or the matching closing quote
//