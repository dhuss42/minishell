/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_space_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:49:09 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/02 15:15:05 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t count_tokens(char *str)
{
	char	quotes;
	size_t	i;
	size_t	counter;

	i = 0;
	counter = 0;
	while (str[i] != '\0')
	{
		while(str[i] == ' ')
			i++;
		if (str[i] == '\'' || str[i] == '\"')
		{
			quotes = str[i++];
			while(str[i] != '\0' && str[i] != quotes)
				i++;
			if (str[i] == quotes)
				i++;
			counter++;
		}
		else if (str[i] != '\0' && str[i] != ' ')
		{
			while (str[i] != '\0' && str[i] != ' ' && str[i] != '\"' && str[i] != '\'')
				i++;
			counter++;
		}
	}
	return (counter);
}

char	*populate_str(char *input, size_t *end)
{
	size_t	start;

	start = *end;
	while (input[*end] != '\0' && input[*end] != ' ' && input[*end] != '\'' && input[*end] != '\"')
		(*end)++;
	return (ft_substr(input, start, (*end - start)));
}

char	*populate_quoted_str(char *input, size_t *end)
{
	char	quotes;
	size_t	start;

	start = *end;
	quotes = input[start];
	(*end)++;
	while (input[*end] != '\0' && input[*end] != quotes)
		(*end)++;
	if (input[*end] == quotes)
		(*end)++;
	return (ft_substr(input, start, (*end - start)));
}

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
		if (input[end] != ' ' && input[end] != '\'' && input[end] != '\"')
		{
			tokens[i++] = populate_str(input, &end);
		}
		else if (input[end] == '\'' || input[end] == '\"')
		{
			tokens[i++] = populate_quoted_str(input, &end);
		}
	}
	tokens[i] = NULL;
	return (tokens);
}

char	**split_space_quotes(char *input)
{
	char	**tokens;
	int		i = 0;

	tokens = malloc(sizeof(char *) * (count_tokens(input) + 1));
	if (!tokens)
		return (NULL);
	printf("%zu\n", count_tokens(input) + 1);
	printf("str: [%s]\n", input);
	tokens = fill_token_list(input, tokens); // problem inside here
	while (tokens[i] != NULL)
    {
		printf("[%d] %s\n", i, tokens[i]);
		i++;
	}
	return (tokens);
}

// int main()
// {
//     size_t len;
//     size_t  i = 0;
//     char **tokens;

//     len = count_tokens("Hello | this << >> $ $ \"THE ULTIMATE           \" TEST!!!!! 'FUCK'");
//     printf("len: %zu\n", len);
//     tokens = split_space_quotes("Hello | this << >> $ $ \"THE ULTIMATE           \" TEST!!!!! 'FUCK'");
//     while (tokens[i] != NULL)
//     {
//         printf("%s\n", tokens[i]);
//         i++;
//     }
//     return (0);
// }