/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:51:14 by dhuss             #+#    #+#             */
/*   Updated: 2024/03/22 11:25:10 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
/* #include <stdio.h> */
#include "libft.h"

static int	ft_strlen_constt(char const *str)
{
	int	count;

	count = 0;
	while (str[count] != '\0')
		count++;
	return (count);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	total_len;
	char	*new_string;

	total_len = ft_strlen_constt(s1) + ft_strlen_constt(s2);
	new_string = (char *)malloc(total_len + 1);
	if (new_string == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		new_string[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		new_string[i + j] = s2[j];
		j++;
	}
	new_string[i + j] = '\0';
	return (new_string);
}

/* int	main(void)
{
	char	s1[] = "";
	char	s2[] = "";

	printf("%s\n", ft_strjoin(s1, s2));
	return (0);
} */
