/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:36:21 by maustel           #+#    #+#             */
/*   Updated: 2023/11/22 12:11:15 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The memcpy() function copies n bytes from memory area src to memory area dst.
If dst and src overlap, behavior is undefined.*/

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*desti;
	char	*source;

	if (!dst && !src)
		return (NULL);
	desti = (char *) dst;
	source = (char *) src;
	i = 0;
	while (i < n)
	{
		desti[i] = source[i];
		i++;
	}
	return (dst);
}

int main()
{
	char src[] = "12345678";
	char dst[] = "abcdefghijklmnop";
	int n = 5;
	printf("%s\n", ft_memcpy(dst, src, n));
	char src1[] = "12345678";
	char dst1[] = "abcdefghijklmnop";
	printf("%s\n", memcpy(dst1, src1, n));

	return (0);
}
