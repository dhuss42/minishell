/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:16:00 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/19 11:13:32 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_eichhoernchen.h"

void	clear_all(char **to_clear)
{
	int	j;

	j = 0;
	while (to_clear[j] != NULL)
	{
		if (to_clear[j])
			free(to_clear[j]);
		j++;
	}
	if (to_clear)
		free(to_clear);
}

void	free_token(void *content)
{
	t_token	*tok;

	tok = (t_token *)content;
	if (tok)
	{
		free(tok->input);
		free(tok);
	}
}

void	free_three(char *str, char *str2, char *str3)
{
	if (str)
		free(str);
	if (str2)
		free(str2);
	if (str3)
		free(str3);
}
