/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:33:42 by maustel           #+#    #+#             */
/*   Updated: 2023/10/26 11:17:01 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Outputs the integer ’n’ to the given file descriptor.*/

int	ft_negative(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return (-1);
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	return (n);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	div;
	int	nb;

	n = ft_negative(n, fd);
	if (n < 0)
		return ;
	nb = n;
	div = 1;
	while (nb > 9)
	{
		nb = nb / 10;
		div = div * 10;
	}
	while (div >= 9)
	{
		ft_putchar_fd((n / div) + '0', fd);
		n = n % div;
		div = div / 10;
	}
	ft_putchar_fd(n + '0', fd);
}

// int main()
// {
// 	int n = -2147483647;
// 	ft_putnbr_fd(n, 1);
// 	return (0);
// }
