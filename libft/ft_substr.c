/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:23:59 by dhuss             #+#    #+#             */
/*   Updated: 2024/03/22 11:26:02 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_strlen_const_unsigned(char const *str)
{
	unsigned int	count;

	count = 0;
	while (str[count] != '\0')
		count++;
	return (count);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*sub_s;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen_const_unsigned(s))
	{
		sub_s = (char *)malloc(1);
		if (sub_s == NULL)
			return (NULL);
		sub_s[0] = '\0';
		return (sub_s);
	}
	if (len > ft_strlen_const_unsigned(s) - start)
		len = ft_strlen_const_unsigned(s) - start;
	sub_s = (char *)malloc((len + 1) * sizeof(char));
	if (sub_s == NULL)
		return (NULL);
	i = start;
	j = 0;
	while (s[i] && j < len)
		sub_s[j++] = s[i++];
	sub_s[j] = '\0';
	return (sub_s);
}

/* int	main(void)
{
	char const		s[] = "hola";
	unsigned int	start;
	size_t			len;

	start = 0;
	len = 4444;
	printf("%s\n", ft_substr(s, start, len));
	return (0);
} */
