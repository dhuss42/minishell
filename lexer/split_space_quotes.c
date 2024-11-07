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
	char	quotes;
	size_t	i;
	size_t	counter;

	i = 0;
	counter = 0;
	while (str[i] != '\0')
	{
		while(str[i] == ' ')
		{
			// printf(YELLOW"[%zu] SKIPPING SPACE: %c\n"WHITE, i, str[i]);
			i++;
		}
		if (str[i] == '\'' || str[i] == '\"')
		{
			quotes = str[i++];
			// printf(YELLOW"[%zu] Found quote: %c\n"WHITE, i - 1, quotes);
			while(str[i] != '\0' && str[i] != quotes)
			{
				// printf(GREEN"[%zu] Inside quotes: %c\n"WHITE, i, str[i]);
				i++;
			}
			if (str[i] == quotes)
			{
				if (str[i + 1] == ' ' || str[i + 1] == '\0')
				{
					counter++;
					// printf(RED"update counter {%zu}\n"WHITE, counter);
				}
				// printf(YELLOW"[%zu] Closing quote found: %c\n"WHITE, i, str[i]);
				i++;
			}
		}
		else if (str[i] != '\0' && str[i] != ' ')
		{
			// printf(YELLOW"ENTER LOOP\n"WHITE);
			while (str[i] != '\0' && str[i] != ' ' && str[i] != '\"' && str[i] != '\'')
			{
				// printf(GREEN"[%zu] current char: %c\n"WHITE, i, str[i]);
				i++;
			}
			// printf(YELLOW"EXIT LOOP\n"WHITE);
			counter++;
			// printf(RED"update counter {%zu}\n"WHITE, counter);
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
	// printf(RED"INSIDE populate_str\n"WHITE);
	while (input[*end] != '\0' && input[*end] != ' ' /* && input[*end] != '\'' && input[*end] != '\"' */)
	{
		// printf(BLUE"[%zu] current char %c\n"WHITE, *end, input[*end]);
		if (input[*end] == '\'' || input[*end] == '\"')
		{
			// printf(YELLOW"[%zu] opening quote %c\n"WHITE, *end, input[*end]);
			quotes = input[*end];
				(*end)++;
			while (input[*end] != '\0' && input[*end] != quotes)
			{
				// printf(GREEN"[%zu] inside quote %c\n"WHITE, *end, input[*end]);
				(*end)++;
			}
			if (input[*end] == quotes)
			{
				// printf(YELLOW"[%zu] closing quote %c\n"WHITE, *end, input[*end]);
				(*end)++;
			}
		}
		else if (input[*end] != '\0' && input[*end] != ' ')
		{
			// printf(MAGENTA"[%zu] ordinary char %c\n"WHITE, *end, input[*end]);
			(*end)++;
		}
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
	// printf(RED"INSIDE fill_token_list\n"WHITE);
	while (input[end] != '\0')
	{
		// printf(BLUE"[%zu] current char fill_token_list %c\n"WHITE, end, input[end]);
		while (input[end] == ' ')
			end++;
		if (input[end] != ' ' /* && input[end] != '\'' && input[end] != '\"' */)
		{
			tokens[i] = populate_str(input, &end);
			if (!tokens[i])
				return (clear_all(tokens), NULL);

			// printf(CYAN"[%zu] TOKEN: %s\n"WHITE, i, tokens[i]);
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

	// printf(RED"inside split_space_quotes\n"WHITE);
	// printf("count_tokens: %zu\n", count_tokens(input));
	tokens = safe_malloc(sizeof(char *) * (count_tokens(input) + 1));
	if (!tokens)
		return (NULL);

	tokens = fill_token_list(input, tokens);
	if (!tokens)
		return (NULL);
	// exit(EXIT_SUCCESS); Debugging 
	// int i = 0;
	// while (tokens[i] != NULL)
	// {
	// 	printf(MAGENTA"[%d]TOKEN: %s\n"WHITE, i, tokens[i]);
	// 	i++;
	// }
	return (tokens);
}
