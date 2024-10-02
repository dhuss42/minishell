/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:04:39 by dhuss             #+#    #+#             */
/*   Updated: 2024/04/23 09:18:07 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putchar_base(unsigned int hex_digit, int *counter)
{
	char	*str;

	str = "0123456789ABCDEF";
	if (write (1, &str[hex_digit], 1) == -1)
	{
		*counter = -1;
		return ;
	}
	(*counter)++;
}

void	ft_putnbr_base(unsigned int n, int *counter)
{
	if (n >= 16)
	{
		ft_putnbr_base(n / 16, counter);
		if (*counter == -1)
			return ;
	}
	if (n >= 0)
	{
		ft_putchar_base(n % 16, counter);
	}
}
