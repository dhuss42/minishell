/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:58:47 by maustel           #+#    #+#             */
/*   Updated: 2023/10/18 14:05:28 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The memcmp() function compares byte string s1 against byte string s2.
Both strings are assumed to be n bytes long.
The memcmp() function returns zero if the two strings are identical,
otherwise returns the difference between the first two differing bytes
it does not stop at a null character*/

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*str1;
	char	*str2;

	i = 0;
	if (n <= 0)
		return (0);
	str1 = (char *) s1;
	str2 = (char *) s2;
	while (i < n)
	{
		if ((unsigned char) str1[i] != (unsigned char) str2[i])
			return ((unsigned char) str1[i] - (unsigned char) str2[i]);
		i++;
	}
	return ((unsigned char) *str1 - (unsigned char) *str2);
}

// int main()
// {
// 	printf("memcmp\n");
// 	char s1[] = "hello";
// 	char s2[] = "hello";
// 	int n = 0;
// 	printf("%d\n", memcmp(s1, s2, n));
// 	if (ft_memcmp(s1, s2, n) == memcmp(s1, s2, n))
// 		printf("Ok!\n");
// 	else
// 		printf("NOT OK!");
// 	return (0);
// }
