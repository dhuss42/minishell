/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:45:46 by maustel           #+#    #+#             */
/*   Updated: 2023/10/19 13:11:44 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*    strlcpy() copies up to dstsize - 1 characters from the
string src to dst, NUL-terminating the result if dstsize is not 0.
it returns the length of src*/

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (i < dstsize - 1 && (src[i]) && dstsize != 0)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize != 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}

// int main()
// {
// 	printf("strlcpy\n");
// 	char src[] = "lorem ipsum dolor sit amet";
// 	char *dst = malloc(sizeof(char) * 16);
// 	int n = 15;
// 	size_t ret = strlcpy(dst, src, n);
// 	printf("%zu\n%s\n", ret, dst);
// 	write(1, dst, 15);
// }
