/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:35:40 by maustel           #+#    #+#             */
/*   Updated: 2023/10/18 16:46:05 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The strnstr() function locates the first occurrence of the null-terminated
string needle in the string hayst, where not more than len characters are
searched. Characters that appear after a `\0' character are not searched.
If needle is an empty string, hayst is returned; if needle occurs nowhere
in hayst, NULL is returned; otherwise a pointer to the first character of
the first occurrence of needle is returned.*/

char	*ft_strnstr(const char *hayst, const char *needle, size_t len)
{
	size_t	i;
	size_t	n;

	if (needle[0] == '\0')
		return ((char *)hayst);
	i = 0;
	n = 0;
	while (hayst[i + n] && i + n < len)
	{
		n = 0;
		while (hayst[i + n] == needle[n] && i + n < len)
		{
			n++;
			if (needle[n] == '\0')
				return ((char *) hayst + i);
		}
		i++;
	}
	return (NULL);
}

// int main()
// {
// 	printf("strnstr\n");
// 	char hayst[] = "lorem ipsum dolor sit amet";
// 	char needle[] = "dolor";
// 	int n = 15;
// 	printf("%s\n", ft_strnstr(hayst, needle, n));
// 	printf("%s\n", strnstr(hayst, needle, n));
// 	if (ft_strnstr(hayst, needle, n) == strnstr(hayst, needle, n))
// 		printf("Ok!\n");
// 	else
// 		printf("NOT OK!");
// 	return (0);
// }
