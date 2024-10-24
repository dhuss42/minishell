/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:50:24 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/10 11:19:11 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_eichhoernchen.h"

token *create_token(token_type type, char *input)
{
	token *new;

	new = malloc(sizeof(token));
	if(!new)
	{
		// print_error(errno, NULL);
		return (NULL);
	}
	new->type = type;
	new->input = ft_strdup(input);
	return (new);
}

// function creates a new token
//	allocates enough mem for the token
//	assigns the type based on the given input
//	saves the input string that corresponds to the token in question

// token	*quote_tokens(char *str)
// {
// 	token	*tok;

// 	tok = NULL;
// 	if (str[0] == '\'')
// 		tok = create_token(TOKEN_SQUOTES, str);
// 	else if (str[0] == '\"')
// 		tok = create_token(TOKEN_DQUOTES, str);
// 	return (tok);
// }

token	*which_token(char *str)
{
	token	*tok;

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
	if(!tok)
		return (NULL);
	return (tok);
}


t_list	*tokeniser(char **split_double_array)
{
	token	*tok;
	t_list	*head;
	t_list	*new;
	size_t	i;

	tok = NULL;
	head = NULL;
	new = NULL;
	i = 0;
	while(split_double_array[i] != NULL)
	{
		tok = which_token(split_double_array[i]);
		if (!tok)
			return (NULL);
		// print_token(tok);
		new = ft_lstnew((void *)tok);
		if (!new)
		{
			free_token(tok);
			// print_error(errno, NULL);
			return (NULL);
		}
		ft_lstadd_back(&head, new);
		i++;
	}
	clear_all(split_double_array);
	return (head);
}

