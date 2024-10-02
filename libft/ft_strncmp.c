/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:51:13 by maustel           #+#    #+#             */
/*   Updated: 2023/10/18 13:48:21 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The strcmp() and strncmp() functions lexicographically compare the null-
terminated strings s1 and s2. The strncmp() function compares not more than
n characters.
Because strncmp() is designed for comparing strings rather than binary data,
characters that appear after a `\0' character are not compared.
The strcmp() and strncmp() functions return an integer greater than, equal to, or
less than 0, according as the string s1 is greater than, equal to, or less than
the string s2.  The comparison is done using unsigned characters,
so that `\200' is greater than `\0'.*/

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && i < n)
	{
		if ((unsigned char) s1[i] != (unsigned char) s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	if (i == n)
		return (0);
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

// int main()
// {
// 	printf("strncmp\n");
// 	char s1[] = "test";
// 	char s2[] = "testss";
// 	int n = 7;
// 	printf("%d\n", strncmp(s1, s2, n));
// 	if (ft_strncmp(s1, s2, n) == strncmp(s1, s2, n))
// 		printf("Ok!\n");
// 	else
// 		printf("NOT OK!");
// 	return (0);
// }
