/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_space_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:49:09 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/09 12:01:47 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_eichhoernchen.h"

size_t count_tokens(char *str)
{
	// char	quotes;
	size_t	i;
	size_t	counter;

	i = 0;
	counter = 0;
	while (str[i] != '\0')
	{
		while(str[i] == ' ')
		{
			printf(YELLOW"[%zu] SKIPPING SPACE: %c\n"WHITE, i, str[i]);
			i++;
		}
		// if (str[i] == '\'' || str[i] == '\"')
		// {
		// 	quotes = str[i++];
		// 	while(str[i] != '\0' && str[i] != quotes)
		// 		i++;
		// 	if (str[i] == quotes)
		// 		i++;
		// 	counter++;
		// }
		/* else */ if (str[i] != '\0' && str[i] != ' ')
		{
			printf(YELLOW"ENTER LOOP\n"WHITE);
			while (str[i] != '\0' && str[i] != ' ' /* && str[i] != '\"' && str[i] != '\'' */)
			{
				printf(GREEN"[%zu] current char: %c\n"WHITE, i, str[i]);
				i++;
			}
			printf(YELLOW"EXIT LOOP\n"WHITE);
			counter++;
			printf(RED"update counter {%zu}\n"WHITE, counter);
		}
	}
	return (counter);
}

// goes through the string
// skipps spaces
// if the current position is not space enter loop
// 

char	*populate_str(char *input, size_t *end)
{
	char	quotes;
	size_t	start;

	quotes = '\0';
	start = *end;
	while (input[*end] != '\0' && input[*end] != ' ' /* && input[*end] != '\'' && input[*end] != '\"' */)
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
		if (input[*end] != '\0' && input[*end] != ' ')
			(*end)++;
	}
	return (ft_substr(input, start, (*end - start)));
}

/* char	*populate_quoted_str(char *input, size_t *end)
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
} */

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
		if (input[end] != ' ' /* && input[end] != '\'' && input[end] != '\"' */)
		{
			tokens[i++] = populate_str(input, &end);
		}
/* 		else if (input[end] == '\'' || input[end] == '\"')
		{
			tokens[i++] = populate_quoted_str(input, &end);
		} */
	}
	tokens[i] = NULL;
	return (tokens);
}

char	**split_space_quotes(char *input)
{
	char	**tokens;

	printf(RED"inside split_space_quotes\n"WHITE);
	printf("count_tokens: %zu\n", count_tokens(input));
	// exit(EXIT_SUCCESS);
	tokens = malloc(sizeof(char *) * (count_tokens(input) + 1));
	if (!tokens)
		return (NULL);
	tokens = fill_token_list(input, tokens);
	int i = 0;
	while (tokens[i] != NULL)
	{
		printf(MAGENTA"[%d]TOKEN: %s\n"WHITE, i, tokens[i]);
		i++;
	}
	return (tokens);
}
