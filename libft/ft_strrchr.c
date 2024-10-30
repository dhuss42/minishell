/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:03:17 by dhuss             #+#    #+#             */
/*   Updated: 2024/03/21 16:05:42 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include <stdio.h>
#include <string.h> */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	end;

	end = 0;
	while (s[end])
		end++;
	while (end >= 0)
	{
		if (s[end] == (unsigned char)c)
			return ((char *) &s[end]);
		end--;
	}
	return (NULL);
}

/* int	main(void)
{
	const char	*s = "Hello";
	char		c;

	c = 'H';
	printf("%s\n", ft_strrchr(s, c));
	printf("%s\n", strrchr(s, c));
	return (0);
} */
