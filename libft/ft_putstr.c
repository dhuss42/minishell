/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 09:48:35 by dhuss             #+#    #+#             */
/*   Updated: 2024/04/23 09:03:41 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr(char *s, int *counter)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		if (write (1, "(null)", 6) == -1)
		{
			*counter = -1;
			return ;
		}
		*counter += 6;
		return ;
	}
	while (s[i])
	{
		if (write (1, &s[i], 1) == -1)
		{
			*counter = -1;
			return ;
		}
		i++;
		(*counter)++;
	}
}
