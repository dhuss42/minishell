/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:41:50 by dhuss             #+#    #+#             */
/*   Updated: 2024/03/11 10:55:51 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include <stdio.h>
#include <string.h> */
#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = (unsigned char *)b;
	while (i < len)
	{
		ptr[i] = c;
		i++;
	}
	return (ptr);
}

/* int	main(void)
{
	char	b[] = "PlsBMemsetMe";
	int		c;
	size_t	len;

	c = 'a';
	len = 3;
	printf("%s\n", ft_memset(b, c, len));
	printf("%s\n", memset(b, c, len));
	return (0);
} */
