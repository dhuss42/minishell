/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:08:19 by dhuss             #+#    #+#             */
/*   Updated: 2024/03/22 11:23:56 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

static int	digits(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

static char	*handle_sign(int *n, int *sign, int num_digits)
{
	char	*s;

	if (*n < 0)
	{
		s = (char *)malloc(num_digits + 2);
		if (s == NULL)
			return (NULL);
		*n *= -1;
		*sign = 1;
		s[num_digits] = '-';
	}
	else
	{
		s = (char *)malloc(num_digits + 1);
		if (s == NULL)
			return (NULL);
	}
	return (s);
}

static char	*ft_swap(char *s, int i)
{
	int		start;
	int		end;
	char	temp;

	start = 0;
	end = i - 1;
	while (start < end)
	{
		temp = s[start];
		s[start] = s[end];
		s[end] = temp;
		start++;
		end--;
	}
	return (s);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		num_digits;
	int		i;
	int		sign;

	num_digits = digits(n);
	i = 0;
	sign = 0;
	if (n < 0)
		sign = 1;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	s = handle_sign(&n, &sign, num_digits);
	if (!s)
		return (NULL);
	while (n > 0)
	{
		s[i++] = n % 10 + 48;
		n = n / 10;
	}
	s = ft_swap(s, (i + sign));
	s[i + sign] = '\0';
	return (s);
}

// int	main(void)
// {
// 	int	n;

// 	n = -2147483648;
// 	printf("%s\n", ft_itoa(n));
// 	return (0);
// }
