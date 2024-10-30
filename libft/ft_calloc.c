/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:01:14 by dhuss             #+#    #+#             */
/*   Updated: 2024/03/14 10:04:48 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
// #include <stdio.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t			total_size;
	size_t			i;
	void			*ptr;
	unsigned char	*fill;

	total_size = count * size;
	i = 0;
	ptr = malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	fill = (unsigned char *) ptr;
	while (i < total_size)
	{
		fill[i] = 0;
		i++;
	}
	return (ptr);
}

/* int	main(void)
{
	size_t	count;
	size_t	size;
	void	*ptr;

	count = 5;
	size = 6;
	ptr = ft_calloc(count, size);
	if (ptr == NULL)
		printf("Memory allocation failed\n");
	else
	{
		printf("Memory allocation successful\n");
		free(ptr);
	}
	ptr = calloc(count, size);
		if (ptr == NULL)
		printf("Original: Memory allocation failed\n");
	else
	{
		printf("Original: Memory allocation successful\n");
		free(ptr);
	}
	return (0);
} */
