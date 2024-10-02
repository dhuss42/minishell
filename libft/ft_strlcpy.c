/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:04:57 by dhuss             #+#    #+#             */
/*   Updated: 2024/03/18 16:24:56 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include <stdio.h>
#include <string.h> */
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (dstsize != '\0')
	{
		while (dstsize > 1 && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
			dstsize--;
		}
		dst[i] = '\0';
	}
	while (src[j] != '\0')
		j++;
	return (j);
}

/* int	main(void)
{
	char	dst[] = "Hello ";
	char	src[] = "lorem ipsum dolor sit amet";
	size_t	dstsize;

	dstsize = 0;
	printf("Before Ft: %s\n", dst);
	printf("%zu\n", ft_strlcpy(dst, src, dstsize));
	printf("After Ft: %s\n", dst);
	printf("%lu\n", strlcpy(dst, src, dstsize));
	printf("After Original: %s\n", dst);
	return (0);
} */
