/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned_fd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:08:32 by dhuss             #+#    #+#             */
/*   Updated: 2024/04/23 09:07:25 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_unsigned(unsigned int n, int *counter)
{
	if (n >= 10)
	{
		ft_putnbr_unsigned(n / 10, counter);
		if (*counter == -1)
			return ;
	}
	if (n >= 0)
		ft_putchar(n % 10 + 48, counter);
}
