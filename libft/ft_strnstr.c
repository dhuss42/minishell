/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:36:10 by dhuss             #+#    #+#             */
/*   Updated: 2024/03/13 12:46:18 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include <string.h>
#include <stdio.h> */
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		j;

	i = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (haystack[i] && i <= len)
	{
		j = 0;
		while (needle[j] && haystack[i + j] == needle[j] && (i + j) < len)
			j++;
		if (needle[j] == '\0')
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}

/* int	main(void)
{
	const char	*haystack = "abcdefgh";
	const char	*needle = "abc";
	size_t		len;

	len = 2;
	printf("%s\n", ft_strnstr(haystack, needle, len));
	printf("%s\n", strnstr(haystack, needle, len));
	return (0);
} */
