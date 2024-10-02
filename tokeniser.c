/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:50:24 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/02 17:29:40 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	print_token(token *tok)
{
	char *token_str;

	token_str = NULL;
	if (tok->type == TOKEN_PIPE)
		token_str = "PIPE";
	else if (tok->type == TOKEN_REDIN)
		token_str = "REDIRECT IN";
	else if (tok->type == TOKEN_REDOUT)
		token_str = "REDIRECT OUT";
	else if (tok->type == TOKEN_HEREDOC)
		token_str = "HEREDOC";
	else if (tok->type == TOKEN_REDAPPEND)
		token_str = "REDIRECTION APPEND";
	else if (tok->type == TOKEN_SQUOTES)
		token_str = "SINGLE QUOTES";
	else if (tok->type == TOKEN_DQUOTES)
		token_str = "DOUBLE QUOTES";
	else if (tok->type == TOKEN_ENVVAR)
		token_str = "ENVIRONMENT VARIABLE";
	else if (tok->type == TOKEN_EXITSTATUS)
		token_str = "EXIT STATUS";
	else if (tok->type == TOKEN_ARGS)
		token_str = "ARGUMENTS";
	else if (tok->type == TOKEN_WORD)
		token_str = "WORD";
	printf("Token\n Type: %s\n Value: %s\n\n", token_str, tok->input);
}

// function prints the Token struct and its contents
//	checks the token_type and changes the value of token_str accordingly

void	print_token_list(t_list *list)
{
	t_list *current = list;

	while (current != NULL)
	{
		token *tok = (token *)(current->content);
		print_token(tok);
		current = current->next;
	}
}

token *create_token(token_type type, char *input)
{
	token *new;

	new = malloc(sizeof(token));
	if(!new)
		return (NULL);
	new->type = type;
	new->input = ft_strdup(input);
	return (new);
}

// function creates a new token
//	allocates enough mem for the token
//	assigns the type based on the given input
//	saves the input string that corresponds to the token in question

token	*quote_tokens(char *str)
{
	token	*tok;

	tok = NULL;
	if (str[0] == '\'')
		tok = create_token(TOKEN_SQUOTES, str);
	else if (str[0] == '\"')
		tok = create_token(TOKEN_DQUOTES, str);
	return (tok);
}

token	*which_token(char *str)
{
	token	*tok;

	tok = NULL;
	if (str[0] == '\'' || str[0] == '\"')
		tok = quote_tokens(str);
	else if (str[0] == '|')
		tok = create_token(TOKEN_PIPE, str);
	else if (str[0] == '<')
		tok = create_token(TOKEN_REDIN, str);
	else if (str[0] == '>')
		tok = create_token(TOKEN_REDOUT, str);
	else if (ft_strncmp(str, "<<", 2) == 0)
		tok = create_token(TOKEN_HEREDOC, str);
	else if (ft_strncmp(str, ">>", 2) == 0)
		tok = create_token(TOKEN_REDAPPEND, str);
	else if (ft_strncmp(str, "$?", 2) == 0)
		tok = create_token(TOKEN_EXITSTATUS, str);
	else if (str[0] == '$' && str[1] != '?')
		tok = create_token(TOKEN_ENVVAR, str);
	else if (str[0] == '-')
		tok = create_token(TOKEN_ARGS, str);
	else
		tok = create_token(TOKEN_WORD, str);
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
		// print_token(tok);
		new = ft_lstnew((void *)tok);
		if (!new)
			free_token(tok);
		ft_lstadd_back(&head, new);

		// create new node with token content
		// add the list to the back
		i++;
	}
	clear_all(split_double_array);
	return (head);
}

