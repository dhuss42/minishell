/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 08:57:21 by dhuss             #+#    #+#             */
/*   Updated: 2024/04/23 09:15:01 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putchar_base_unsigned(unsigned long hex_digit, int *counter)
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

static void	ft_putnbr_unsigned_long(unsigned long n, int *counter)
{
	if (*counter == -1)
		return ;
	if (n >= 10)
		ft_putnbr_unsigned_long(n / 16, counter);
	if (n > 0)
		ft_putchar_base_unsigned(n % 16, counter);
}

void	ft_putptr(void *ptr, int *counter)
{
	unsigned long	adress;

	adress = (unsigned long) ptr;
	ft_putstr("0x", counter);
	if (*counter == -1)
		return ;
	if (adress == 0)
	{
		ft_putchar('0', counter);
		if (*counter == -1)
			return ;
	}
	ft_putnbr_unsigned_long(adress, counter);
}
