/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:00:02 by dhuss             #+#    #+#             */
/*   Updated: 2024/03/22 11:24:53 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "libft.h" */
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static int	word_count(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (count);
}

static void	ft_free(char **ptr, int x)
{
	int	i;

	i = 0;
	while (i < x)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

static char	*fill_word(const char *ptr, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc(sizeof(char ) *(end - start + 1));
	if (!word)
		return (NULL);
	while (start < end)
	{
		word[i] = ptr[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

static char	**fill_ptr_array(char const *s, char c, char **ptr)
{
	int	start;
	int	end;
	int	x;

	start = 0;
	end = 0;
	x = 0;
	while (s[end] != '\0')
	{
		if (s[end] != c)
		{
			start = end;
			while (s[end] && s[end] != c)
				end++;
			ptr[x] = fill_word(s, start, end);
			if (!(ptr[x]))
				return (ft_free(ptr, x), NULL);
			x++;
		}
		else
			end++;
	}
	ptr[x] = NULL;
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;

	ptr = malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!ptr)
		return (NULL);
	ptr = fill_ptr_array(s, c, ptr);
	return (ptr);
}

/* int	main(void)
{
	char	s[] = "      split       this for   me  !";
	char	**result;
	char	c;
	int		i;

	c = ' ';
	result = ft_split(s, c);
	i = 0;
	if (result)
	{
		while (result[i])
		{
			printf("%s\n", result[i]);
			free(result[i]);
			i++;
		}
		free(result);
	}
	return (0);
} */
