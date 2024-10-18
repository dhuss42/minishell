/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:41:51 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/18 17:02:26 by dhuss            ###   ########.fr       */
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
	char	quote;
	char	*tmp;

	tmp = NULL;
	quote = row->args[expand->i][expand->k];
	expand->k++;
	while (row->args[expand->i][expand->k] != quote && row->args[expand->i][expand->k] != '\0')
	{
		if (row->args[expand->i][expand->k] == '\0')
		{
			printf("TEST19\n");
			break ;
		}
		if (row->args[expand->i][expand->k] == '$' && ft_isalnum(row->args[expand->i][expand->k + 1]))
		{
			tmp = tmp_dollar(row, expand);
			get_expanded_2(tmp, env, row, expand);
		}
		if (tmp)
		{
			free(tmp);
			tmp = NULL;
		}
		if (!(row->args[expand->i][expand->k] == '$' && ft_isalnum(row->args[expand->i][expand->k + 1])))
		{
			printf("row->args[expand->i][k]: %c\n", row->args[expand->i][expand->k - 1]);
			printf("TEST20\n");
			expand->k++;
		}
	}
}

// not implemented yet, need to fix issues with the break loop
// maybe just use a struct