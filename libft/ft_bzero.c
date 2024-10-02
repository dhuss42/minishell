/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:56:20 by dhuss             #+#    #+#             */
/*   Updated: 2024/03/13 10:57:00 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include <stdio.h>
#include <string.h> */
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}
}

/* int	main(void)
{
	char	b[] = "PlsBZero";
	size_t	n;

	n = 20;
	printf("Before Ft and Original: %s\n", b);
	ft_bzero(b, n);
	printf("After Ft: %s\n", b);
	printf("After Original: %s\n", bzero(b, n));
	return (0);
} */
