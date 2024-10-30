/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:41:23 by maustel           #+#    #+#             */
/*   Updated: 2023/10/14 10:09:44 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The atoi() function converts the initial portion of the string
pointed to by str to int representation.*/

int	ft_atoi(const char *str)
{
	int	nbr;
	int	minus;

	while ((*str < 14 && *str > 8) || *str == 32)
		str++;
	minus = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus = -1;
		str++;
	}
	nbr = 0;
	while (str && '0' <= *str && *str <= '9')
	{
		nbr = nbr * 10 + (*str - '0');
		str++;
	}
	return (nbr * minus);
}

// int main()
// {
// 	char str[] = "   + 6";
// 	printf("%d\n", atoi(str));
// 	if (ft_atoi(str) == atoi(str))
// 		printf("Ok!\n");
// 	else
// 		printf("NOT OK!\n");

// 	return (0);
// }
