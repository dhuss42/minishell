/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:41:51 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/18 16:31:17 by dhuss            ###   ########.fr       */
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

void	quotes(t_command *row, size_t *i, size_t *k, char **env)
{
	char	quote;
	char	*tmp;

	tmp = NULL;
	quote = row->args[*i][*k];
	(*k)++;
	while (row->args[*i][*k] != quote && row->args[*i][*k] != '\0')
	{
		if (row->args[*i][*k] == '\0')
		{
			printf("TEST19\n");
			break ;
		}
		if (row->args[*i][*k] == '$' && ft_isalnum(row->args[*i][*k + 1]))
		{
			tmp = tmp_dollar(row, i, k);
			get_expanded_2(tmp, env, row, i, k);
		}
		if (tmp)
		{
			free(tmp);
			tmp = NULL;
		}
		if (!(row->args[*i][*k] == '$' && ft_isalnum(row->args[*i][*k + 1])))
		{
			printf("row->args[*i][k]: %c\n", row->args[*i][*k - 1]);
			printf("TEST20\n");
			k++;
			printf("row->args[*i][k]: %c\n", row->args[*i][*k - 1]);
		}
	}
}

// not implemented yet, need to fix issues with the break loop
// maybe just use a struct