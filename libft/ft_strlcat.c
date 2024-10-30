/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:52:15 by maustel           #+#    #+#             */
/*   Updated: 2023/10/19 14:27:09 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* strlcat() appends string src to the end of dst.
It will append at most dstsize - strlen(dst) - 1 characters.
It will then NUL-terminate, unless dstsize is 0 or the original
dst string was longer than dstsize.
It returns the initial length of dst plus the length of src.*/

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	size;
	size_t	i;

	size = ft_strlen(dst);
	if (ft_strlen(src) == 0)
		return (size);
	if (dstsize <= size || dstsize == 0)
		return (dstsize + ft_strlen(src));
	i = 0;
	while (i < (dstsize - size - 1) && src[i])
	{
		dst[size + i] = src[i];
		i++;
	}
	if (dstsize > 0 && dstsize > size)
		dst[size + i] = '\0';
	return (size + ft_strlen(src));
}

// int main()
// {
// 	printf("strlcat\n");
// 	char *src = strdup("abcd");
// 	char *dst = strdup("pqrstuvwxyz");
// 	// dst[10] = 'a';
// 	/* char dst[] = "123456789012345678";
// 	--> READ ONLY. doesnt work here, because dst gets transformed*/
// 	int dstsize = 20;
// 	printf("%zu\n%s\n", ft_strlcat(dst, src, dstsize), dst);
// }
