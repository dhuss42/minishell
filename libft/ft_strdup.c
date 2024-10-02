/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:46:41 by dhuss             #+#    #+#             */
/*   Updated: 2024/03/14 10:13:18 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include <string.h>
#include <stdio.h> */
#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = 0;
	while (s1[i] != '\0')
		i++;
	ptr = (char *) malloc (i + 1);
	if (ptr == NULL)
		return (NULL);
	j = 0;
	while (j < i)
	{
		ptr[j] = s1[j];
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}

/* int	main(void)
{
	const char	s1[] = "PlsCopyMe";
	char		*ptr;

	printf("Ft: %s\n", ft_strdup(s1));
	ptr = ft_strdup(s1);
		if (ptr == NULL)
		printf("Memory allocation failed\n");
	else
	{
		printf("Memory allocation and string copy successful\n");
		free(ptr);
	}
	printf("Ft: %s\n", strdup(s1));
	return (0);
} */
