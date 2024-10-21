/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:41:51 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/21 16:00:52 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_eichhoernchen.h"

bool	should_expand(char *str, size_t k)
{
	size_t	i;
	size_t	open_quotes;
	size_t	closing_quotes;

	i = k;
	open_quotes = 0;
	closing_quotes = 0;
	while (str[i] == '\'')
	{
		i++;
		open_quotes++;
	}
	while (str[i] != '\0' && str[i] != '\'')
		i++;
	while (str[i] == '\'' && str[i] != '\0')
	{
		i++;
		closing_quotes++;
	}
	if (open_quotes - closing_quotes == 0 && open_quotes % 2 == 0 && closing_quotes % 2 == 0)
		return (true);
	return (false);
}
	// while the string is equal to ' move i and increase nbr of quotes
	// while the string does not equal 0 or ' skip
	//increase nbr of closing quotes
	// if diff 0 and if open and closing % 2 = 0
	//then true:

void	quotes(t_command *row, t_shell *expand, char **env)
{
	char	*tmp;
	size_t	counter = 0;

	tmp = NULL;
	expand->quote = row->args[expand->i][expand->k];
	while (row->args[expand->i][expand->k] == expand->quote && counter != 2)
	{
		expand->k++;
		counter++;
	}
	while (row->args[expand->i][expand->k] != expand->quote && row->args[expand->i][expand->k] != '\0' && counter != 2)
	{
		if (row->args[expand->i][expand->k] == '\0')
			break ;
		if (row->args[expand->i][expand->k] == '$' && ft_isalnum(row->args[expand->i][expand->k + 1]))
		{
			tmp = tmp_dollar(row, expand);
			get_expanded(tmp, env, row, expand);
			if (tmp)
			{
				free(tmp);
				tmp = NULL;
				expand->k++;
				break ;
			}
		}
		if (!(row->args[expand->i][expand->k] == '$' && ft_isalnum(row->args[expand->i][expand->k + 1])))
		{
			expand->k++;
		}
	}
}
