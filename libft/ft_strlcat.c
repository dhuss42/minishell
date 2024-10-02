/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:04:57 by dhuss             #+#    #+#             */
/*   Updated: 2024/09/09 12:14:16 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include <stdio.h>
#include <string.h> */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dest_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	dest_len = ft_strlen(dst);
	if (dest_len >= dstsize)
		dest_len = dstsize;
	if (dest_len == dstsize)
		return (dest_len + src_len);
	if (src_len < dstsize - dest_len)
		ft_memcpy(dst + dest_len, src, src_len + 1);
	else
	{
		ft_memcpy(dst + dest_len, src, dstsize - dest_len - 1);
		dst[dstsize - 1] = '\0';
	}
	return (src_len + dest_len);
}

/* int	main(void)
{
	char	dst[] = "rrrrrrrrrrrrrrrr";
	char	src[] = "lorem ipsum dolor sit amet";
	size_t	dstsize;

	dstsize = 5;
	printf("Before Ft: %s\n", dst);
	printf("%zu\n", ft_strlcat(dst, src, dstsize));
	printf("After Ft: %s\n", dst);
	printf("%lu\n", strlcat(dst, src, dstsize));
	printf("After Original: %s\n", dst);
	return (0);
} */
