/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:10:22 by maustel           #+#    #+#             */
/*   Updated: 2023/11/15 12:14:50 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The bzero() function writes n zeroed bytes to the string s.
If n is zero, bzero() does nothing.*/

void	ft_bzero(void *s, size_t n)
{
	if (n == 0)
		return ;
	ft_memset (s, 0, n);
}

// int main()
// {
// 	printf("bzero\n");
// 	char s[] = "Ciao bello";
// 	int n = 1;
// 	ft_bzero(s, n);
// 	printf("%s\n", s);
// 	char b[] = "Ciao bello";
// 	bzero(b, n);
// 	printf("%s\n", b);
// 	return (0);
// }
