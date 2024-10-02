/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:04:36 by dhuss             #+#    #+#             */
/*   Updated: 2024/03/11 11:17:07 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include <stdio.h>
#include <string.h> */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		if (ptr[i] == (unsigned char)c)
			return ((void *)(ptr + i));
		i++;
	}
	return (NULL);
}

/* int	main(void)
{
	char	s[] = "PleaseLookHere";
	char	c;
	size_t	n;

	c = 'e';
	n = 8;
	printf("%s\n", ft_memchr(s, c, n));
	printf("%s\n", memchr(s, c, n));
	return (0);
} */
