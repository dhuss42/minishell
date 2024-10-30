/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:24:12 by maustel           #+#    #+#             */
/*   Updated: 2023/10/19 13:37:38 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The strchr() function locates the first occurrence of c (converted to a char)
in the string pointed to by s. The terminating null character is considered to
be part of the string; therefore if c is `\0', the functions locate the
terminating `\0'.
It returns a pointer to the located character, or NULL if the character
does not appear in the string.*/

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char) c)
			return ((char *) s);
		s++;
	}
	if (*s == (char) c)
		return ((char *)s);
	return (NULL);
}

// int main()
// {
// 	char s[] = "teste";
// 	int c = '\0';
// 	printf("%s", ft_strchr(s, c));

// 	return (0);
// }
