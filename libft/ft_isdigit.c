/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:29:51 by maustel           #+#    #+#             */
/*   Updated: 2023/10/10 13:43:12 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	else
		return (0);
}

// #include <stdio.h>
// #include <ctype.h>
// int main ()
// {
// 	printf("isdigit\n");
//     int c = 'a';
//     if (ft_isdigit(c) == isdigit(c))
//         printf("Ok!\n");
//     c = '9';
//     if (ft_isdigit(c) == isdigit(c))
//         printf("Ok!\n");
// }