/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:03:14 by maustel           #+#    #+#             */
/*   Updated: 2023/10/26 10:34:19 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*According to the man the memset function writes len bytes of value c
 * (converted to an unsigned char) to the string b. This function returns it's
 * first argument.*/
/*	p = (char *)b;
	casts the void pointer b to a character pointer p.
	This is necessary because you can't directly dereference a void pointer.*/

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		p[i] = (unsigned char) c;
		i++;
	}
	return (b);
}

// #include <stdio.h>
// #include <unistd.h>
// #include <string.h>

// int main()
// {
// 	printf("memset\n");
// 	char b[] = "Hello you!                     ";
// 	int c = 'x';
// 	unsigned int len = 5;
// 	printf("%s\n", ft_memset(b , c, len));
// 	if (ft_memset(b, c, len) == memset(b , c, len))
// 		printf("Ok!");
// 	else
// 		printf("unexpected output!");
// 	return (0);
// }
