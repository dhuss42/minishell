/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:04:39 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/03 14:45:13 by maustel          ###   ########.fr       */
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
	ft_putchar_base(n % 16, counter);
}
