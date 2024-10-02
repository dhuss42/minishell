/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:25:52 by dhuss             #+#    #+#             */
/*   Updated: 2024/03/21 10:09:27 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write (fd, "-2147483648", 11);
	}
	else if (n < 0)
	{
		write (fd, "-", 1);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	if (n >= 0)
		ft_putchar_fd(n % 10 + 48, fd);
}

/* int	main(void)
{
	int	n;
	int	fd;

	n = -2147483648;
	fd = 1;
	ft_putnbr_fd(n, fd);
	return (0);
} */
