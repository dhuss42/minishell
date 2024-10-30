/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:22:01 by dhuss             #+#    #+#             */
/*   Updated: 2024/03/21 11:52:48 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* void	ft_toupper_test(unsigned int index, char *c)
{
	(void)index;
	if (*c >= 97 && *c <= 122)
		*c -= 32;
} */

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		(*f)(i, &s[i]);
		i++;
	}
}

/* int	main(void)
{
	char	s[] = "This is the String";

	printf("Original: %s\n", s);
	ft_striteri(s, ft_toupper_test);
	printf("After: %s\n", s);
	return (0);
} */
