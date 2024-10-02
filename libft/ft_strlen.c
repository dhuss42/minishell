/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:49:42 by dhuss             #+#    #+#             */
/*   Updated: 2024/03/18 14:24:06 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include <stdio.h>
#include <string.h> */
#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (str[count] != '\0')
		count++;
	return (count);
}

/* int	main(void)
{
	char	*c;

	c = "Hello!";
	printf("%d\n", ft_strlen(c));
	printf("%lu\n", strlen(c));
	return (0);
} */
