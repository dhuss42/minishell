/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:47:46 by maustel           #+#    #+#             */
/*   Updated: 2023/10/19 13:10:53 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The strdup() function returns a pointer to a new string which is a duplicate
of the string s. Memory for the new string is obtained with malloc(3), and can
be freed with free(3).*/

char	*ft_strdup(const char *s)
{
	char	*str;
	int		i;

	str = (char *) malloc(sizeof(*s) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

// int main()
// {
// 	char *s = ft_strdup("Hallo du kleiner Vogel");
// 	printf("%s\n", s);
// 	free(s);
// 	return (0);
// }
