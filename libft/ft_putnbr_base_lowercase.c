/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_lowercase.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:04:18 by dhuss             #+#    #+#             */
/*   Updated: 2024/04/22 11:57:31 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putchar_hex_lc(unsigned int hex_digit, int *counter)
{
	char	*str;

	str = "0123456789abcdef";
	if (write (1, &str[hex_digit], 1) == -1)
	{
		*counter = -1;
		return ;
	}
	(*counter)++;
}

void	ft_putnbr_base_lowercase(unsigned int n, int *counter)
{
	if (n >= 16)
	{
		ft_putnbr_base_lowercase(n / 16, counter);
		if (*counter == -1)
			return ;
	}
	ft_putchar_hex_lc(n % 16, counter);
}
