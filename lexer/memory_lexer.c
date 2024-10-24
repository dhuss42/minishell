/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:16:00 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/10 11:19:02 by dhuss            ###   ########.fr       */
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
	token *tok = (token *)content;
	if (tok)
	{
		free(tok->input);
		free(tok);
	}
}

void    free_lexer(char *input, char *trim_inpt, char *res)
{
    if (input)
        free(input);
    if (trim_inpt)
        free(trim_inpt);
    if (res)
        free(res);
}
