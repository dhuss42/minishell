/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:25:52 by dhuss             #+#    #+#             */
/*   Updated: 2024/04/23 09:05:38 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int n, int *counter)
{
	if (*counter == -1)
		return ;
	if (n == -2147483648)
	{
		ft_putstr("-2147483648", counter);
	}
	else if (n < 0)
	{
		ft_putchar('-', counter);
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10, counter);
		if (*counter == -1)
			return ;
	}
	if (n >= 0)
		ft_putchar(n % 10 + 48, counter);
}
