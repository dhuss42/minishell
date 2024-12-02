/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_space_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:49:09 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/19 12:11:05 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	count_tokens_quotes(char *str, size_t *i, size_t *counter)
{
	char	quotes;

	quotes = str[(*i)++];
	while (str[*i] != '\0' && str[*i] != quotes)
	{
		(*i)++;
	}
	if (str[*i] == quotes)
	{
		if (str[*i + 1] == ' ' || str[*i + 1] == '\0')
		{
			(*counter)++;
		}
		(*i)++;
	}
}

size_t	count_tokens(char *str)
{
	size_t	i;
	size_t	counter;

	i = 0;
	counter = 0;
	while (str[i] != '\0')
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '\'' || str[i] == '\"')
			count_tokens_quotes(str, &i, &counter);
		else if (str[i] != '\0' && str[i] != ' ')
		{
			while (str[i] != '\0' && str[i] != ' '
				&& str[i] != '\"' && str[i] != '\'')
				i++;
			counter++;
		}
	}
	return (counter);
}

// goes through the string
// skipps spaces
// if the current position is not space enter loop
// if the loop reaches the end or a space then stop and increase counter

char	*populate_str(char *input, size_t *end)
{
	char	quotes;
	size_t	start;

	quotes = '\0';
	start = *end;
	while (input[*end] != '\0' && input[*end] != ' ')
	{
		if (input[*end] == '\'' || input[*end] == '\"')
		{
			quotes = input[*end];
			(*end)++;
			while (input[*end] != '\0' && input[*end] != quotes)
				(*end)++;
			if (input[*end] == quotes)
				(*end)++;
		}
		else if (input[*end] != '\0' && input[*end] != ' ')
			(*end)++;
	}
	return (safe_ft_substr(input, start, (*end - start)));
}

//goes through string
//

char	**fill_token_list(char *input, char **tokens)
{
	size_t	end;
	size_t	i;

	i = 0;
	end = 0;
	while (input[end] != '\0')
	{
		while (input[end] == ' ')
			end++;
		if (input[end] != ' ')
		{
			tokens[i] = populate_str(input, &end);
			if (!tokens[i])
				return (clear_all(tokens), NULL);
			i++;
		}
	}
	tokens[i] = NULL;
	return (tokens);
}

// function goes through string
// skipps space
// if there no space populate the str and increment the Token double char
// set to NULL

char	**split_space_quotes(char *input)
{
	char	**tokens;

	tokens = safe_malloc(sizeof(char *) * (count_tokens(input) + 1));
	if (!tokens)
		return (NULL);
	tokens = fill_token_list(input, tokens);
	if (!tokens)
		return (NULL);
	return (tokens);
}
