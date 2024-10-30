/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:48:34 by maustel           #+#    #+#             */
/*   Updated: 2023/10/19 13:11:59 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Allocates (with malloc(3)) and returns a copy of
’s1’ with the characters specified in ’set’ removed
from the beginning and the end of the string.
s1: The string to be trimmed.
set: The reference set of characters to trim.*/

int	char_in_set(char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		start;
	int		end;

	i = 0;
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && char_in_set((char *) set, s1[start]))
		start++;
	while (end >= start && char_in_set((char *) set, s1[end]))
		end--;
	str = (char *) malloc (sizeof(const char) * (end - start + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (start <= end)
		str[i++] = s1[start++];
	str[i] = 0;
	return (str);
}

// int main()
// {
// 	char	s1[] = " lorem ipsum dolor sit amet";
// 	char	set[] = "l ";

// 	printf("%s\n", ft_strtrim(s1, set));

// 	return (0);

// }
