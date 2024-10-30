/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:47:13 by maustel           #+#    #+#             */
/*   Updated: 2023/10/26 10:51:20 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The calloc() function contiguously allocates enough space for count objects
that are size bytes of memory each and returns a pointer to the allocated
memory. The allocated memory is filled with bytes of value zero.*/

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count * size > 2147483647)
		return (NULL);
	ptr = (void *) malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

// int main()
// {
// 	int count = 0;
// 	int size = (char) 0;
// 	printf("%p\n", ft_calloc (count, size));

// 	return (0);
// }
