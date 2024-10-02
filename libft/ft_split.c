/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:48:47 by maustel           #+#    #+#             */
/*   Updated: 2023/10/20 11:52:49 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Allocates (with malloc(3)) and returns an array
of strings obtained by splitting ’s’ using the
character ’c’ as a delimiter (Trennzeichen). The array must end
with a NULL pointer.*/

char	*ft_words(char *s, char c, char **str, int n)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (*s == c)
		s++;
	while (s[count] != '\0' && s[count] != c)
	{
		count++;
		i++;
	}
	str[n] = (char *) malloc(sizeof(const char) * (i + 1));
	if (!str[n])
		return (NULL);
	i = 0;
	while (i < count)
	{
		str[n][i] = *s;
		s++;
		i++;
	}
	s++;
	str[n][i] = '\0';
	return (s);
}

int	ft_count_words(const char *s, char c)
{
	int		nbr;
	int		i;
	int		n;

	i = 0;
	nbr = 0;
	n = 1;
	while (s[i])
	{
		if (n == 1 && s[i] != c)
		{
			nbr++;
			n = 0;
		}
		else if (s[i] == c)
			n = 1;
		i++;
	}
	return (nbr);
}

void	ft_freeall(char **str)
{
	int	n;

	n = 0;
	while (str[n])
	{
		free(str[n]);
		n++;
	}
	free (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		nbr;
	int		n;

	if (!s)
		return (NULL);
	nbr = ft_count_words(s, c);
	str = (char **) malloc(sizeof(char *) * (nbr + 1));
	if (!str)
		return (NULL);
	n = 0;
	while (n < nbr)
	{
		s = ft_words((char *) s, c, str, n);
		if (!s)
		{
			ft_freeall(str);
			return (NULL);
		}
		n++;
	}
	str[n] = NULL;
	return (str);
}

// int main()
// {
// 	// char	s1[] = "Hallo_du_Amsel";
// 	char	s1[] = "hello!";
// 	// char	s1[] = "hallo *du *piccolo Amsel *****furbo!";
// 	// char	*s1 = NULL;
// 	char	c = ' ';
// 	char 	**str;

// 	str = ft_split(s1, c);
// 	int n = 0;
// 	if (str != NULL)
// 	{
// 		while (str[n])
// 		{
// 			printf("%s\n", (str[n]));
// 			n++;
// 		}
// 	}
// 	n = 0;
// 	while (str[n])
// 	{
// 		free(str[n]);
// 		n++;
// 	}
// 	free (str);
// 	return (0);
// }
