/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:12:25 by dhuss             #+#    #+#             */
/*   Updated: 2024/03/18 15:10:59 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include <string.h>
#include <stdio.h> */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*ptr_dst;
	unsigned char	*ptr_src;

	ptr_dst = (unsigned char *)dst;
	ptr_src = (unsigned char *)src;
	if (ptr_dst < ptr_src)
	{
		i = 0;
		while (i < len)
		{
			ptr_dst[i] = ptr_src[i];
			i++;
		}
	}
	else if (ptr_dst > ptr_src)
	{
		i = len;
		while (i > 0)
		{
			ptr_dst[i - 1] = ptr_src[i - 1];
			i--;
		}
	}
	return (dst);
}

/* int	main(void)
{
	char	dst[] = "AAAAAAAAAAAAAAAAAAAAAAAAAA";
	char	src[] = "ILikeToMoveit";
	size_t	len;

	len = 8;
	printf("%s\n", ft_memmove(dst, src, len));
	printf("%s\n", memmove(dst, src, len));
	return (0);
} */
