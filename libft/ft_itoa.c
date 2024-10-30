/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:48:57 by maustel           #+#    #+#             */
/*   Updated: 2023/10/19 12:58:49 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Allocates (with malloc(3)) and returns a string
representing the integer received as an argument.
Negative numbers must be handled.*/

char	*ft_digits(int n, char *str, int i, int size)
{
	int	dig;

	dig = 1;
	while (size > 1)
	{
		dig = dig * 10;
		size--;
	}
	while (dig > 1)
	{
		str[i++] = (n / dig) + '0';
		n = n % dig;
		dig = dig / 10;
	}
	str[i++] = n + '0';
	str[i] = 0;
	return (str);
}

int	ft_size(int n)
{
	int	dig;

	dig = 1;
	while (n > 9)
	{
		n = n / 10;
		dig++;
	}
	return (dig);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		neg;
	int		size;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	neg = 0;
	if (n < 0)
	{
		neg = 1;
		n = -n;
	}
	size = ft_size(n);
	str = (char *) malloc (sizeof(char) * (neg + size + 1));
	if (!str)
		return (NULL);
	i = 0;
	if (neg == 1)
		str[i++] = '-';
	str = ft_digits(n, str, i, size);
	return (str);
}

// int main()
// {
// 	int	n = 1000034;
// 	char	*s;
// 	s = ft_itoa(n);
// 	printf("%s\n", s);
// 	free (s);
// 	return (0);
// }
