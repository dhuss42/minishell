/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:39:03 by maustel           #+#    #+#             */
/*   Updated: 2023/10/19 13:40:16 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The strrchr() function is identical to strchr(), except it locates the last
occurrence of c.*/

char	*ft_strrchr(const char *s, int c)
{
	int	size;
	int	i;

	size = ft_strlen(s);
	if ((char) c == s[size])
		return ((char *)s + size);
	i = size - 1;
	while (i >= 0)
	{
		if (s[i] == (char) c)
			return ((char *) s + i);
		i--;
	}
	return (NULL);
}

// int main()
// {
// 	char s[] = "12a34a567a8";
// 	int c = 'a';
// 	printf("%s", ft_strrchr(s, c));

// 	return (0);
// }
