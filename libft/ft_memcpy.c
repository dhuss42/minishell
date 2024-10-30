/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:35:11 by dhuss             #+#    #+#             */
/*   Updated: 2024/03/21 09:38:06 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include <stdio.h>
#include <string.h> */
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*ptr_dest;
	char	*ptr_soruce;

	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	ptr_dest = (char *)dst;
	ptr_soruce = (char *)src;
	while (i < n)
	{
		ptr_dest[i] = ptr_soruce[i];
		i++;
	}
	return ((void *)dst);
}

/* int	main(void)
{
	// char	dst[] = "AAAAAAAAAAAAA";
	char	src[] = "PleaseCopy";
	size_t	n;

	n = 3;
	printf("%s\n", ft_memcpy(src, src + 4, n));
	printf("%s\n", memcpy(src, src + 4, n));
	return (0);
} */
