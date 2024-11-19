/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:50:24 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/19 12:11:14 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*create_token(t_token_type type, char *input)
{
	t_token	*new;

	new = safe_malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->input = ft_strdup(input);
	return (new);
}

// function creates a new token
//	allocates enough mem for the token
//	assigns the type based on the given input
//	saves the input string that corresponds to the token in question

t_token	*which_token(char *str)
{
	t_token	*tok;

	tok = NULL;
	if (str[0] == '|')
		tok = create_token(TOKEN_PIPE, str);
	else if (str[0] == '<')
		tok = create_token(TOKEN_REDIN, str);
	else if (str[0] == '>')
		tok = create_token(TOKEN_REDOUT, str);
	else if (ft_strncmp(str, "<<", 2) == 0)
		tok = create_token(TOKEN_HEREDOC, str);
	else if (ft_strncmp(str, ">>", 2) == 0)
		tok = create_token(TOKEN_REDAPPEND, str);
	else
		tok = create_token(TOKEN_WORD, str);
	if (!tok)
		return (NULL);
	return (tok);
}

t_list	*tokeniser(char **split_double_array)
{
	t_token	*tok;
	t_list	*head;
	t_list	*new;
	size_t	i;

	tok = NULL;
	head = NULL;
	new = NULL;
	i = 0;
	while (split_double_array[i] != NULL)
	{
		tok = which_token(split_double_array[i]);
		if (!tok)
			return (NULL);
		new = ft_lstnew((void *)tok);
		if (!new)
		{
			print_error(errno, NULL, PRINT);
			return (free_token(tok), NULL);
		}
		ft_lstadd_back(&head, new);
		i++;
	}
	clear_all(split_double_array);
	return (head);
}
