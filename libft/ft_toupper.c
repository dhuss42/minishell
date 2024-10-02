/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:01:06 by maustel           #+#    #+#             */
/*   Updated: 2023/10/11 14:17:33 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*  The toupper() function converts a lower-case letter to the corresponding
upper-case letter.  The argument must be representable as an unsigned char
or the value of EOF.
If the argument is a lower-case letter, the toupper() function returns the
corresponding upper-case letter if there is one; otherwise,
the argument is returned unchanged.*/

int	ft_toupper(int c)
{
	if ('a' <= c && c <= 'z')
		return (c - 32);
	else
		return (c);
}

// int main()
// {
// 	printf("toupper\n");
// 	char c = 'v';
// 	printf("%d\n%d\n", c, ft_toupper(c));
// 	if (ft_toupper(c) == toupper(c))
// 		printf("Ok!");
// 	else
// 		printf("NOT OK!");
// 	return (0);
// }
