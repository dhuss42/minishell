/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:03:17 by dhuss             #+#    #+#             */
/*   Updated: 2024/03/21 10:23:08 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include <stdio.h>
#include <string.h> */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != (char) c)
	{
		if (s[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *) &s[i]);
}

/* int	main(void)
{
	const char	*s = "teste";
	char		c;

	c = 'e';
	printf("%d\n", ft_strchr(s, c) == s);
	printf("%d\n", strchr(s, c) == s);
	return (0);
} */
