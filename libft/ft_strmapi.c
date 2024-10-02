/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:51:01 by dhuss             #+#    #+#             */
/*   Updated: 2024/03/21 11:18:39 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* char	ft_toupper_test(unsigned int index, char c)
{
	index = 0;
	if (c >= 97 && c <= 122)
		c -= 32;
	return (c);
} */

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*new_s;
	size_t			len;

	len = ft_strlen(s);
	new_s = malloc((len + 1) * sizeof(char));
	if (!new_s)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_s[i] = (*f)(i, s[i]);
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}

/* int	main(void)
{
	char	s[] = "ThisString";
	char	*result;

	printf("Original string: %s\n", s);
	result = ft_strmapi(s, &ft_toupper_test);
	printf("Mapped string: %s\n", result);
	free(result);
	return (0);
} */
