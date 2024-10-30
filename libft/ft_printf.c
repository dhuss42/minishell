/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:02:57 by dhuss             #+#    #+#             */
/*   Updated: 2024/04/29 14:09:23 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	formants(va_list ptr, const char *str, int i, int *counter)
{
	if (str[i + 1] == 'c')
		ft_putchar((va_arg(ptr, int)), counter);
	if (str[i + 1] == 's')
		ft_putstr((va_arg(ptr, char *)), counter);
	if (str[i + 1] == 'p')
		ft_putptr(va_arg(ptr, void *), counter);
	if (str[i + 1] == 'd' || str[i + 1] == 'i')
		ft_putnbr((va_arg(ptr, int)), counter);
	if (str[i + 1] == 'u')
		ft_putnbr_unsigned(va_arg(ptr, unsigned int), counter);
	if (str[i + 1] == 'x')
		ft_putnbr_base_lowercase(va_arg(ptr, unsigned int), counter);
	if (str[i + 1] == 'X')
		ft_putnbr_base(va_arg(ptr, unsigned int), counter);
	if (str [i + 1] == '%')
		ft_putchar('%', counter);
	if (*counter == -1)
		return ;
}

int	ft_printf(const char *str, ...)
{
	va_list	ptr;
	int		i;
	int		counter;

	va_start(ptr, str);
	i = 0;
	counter = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '%')
		{
			ft_putchar(str[i++], &counter);
			if (counter == -1)
				return (-1);
		}
		if (str[i] == '%')
		{
			formants(ptr, str, i, &counter);
			if (counter == -1)
				return (-1);
			i += 2;
		}
	}
	va_end(ptr);
	return (counter);
}
