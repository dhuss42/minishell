/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:17:54 by maustel           #+#    #+#             */
/*   Updated: 2023/10/11 14:22:46 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The tolower() function converts an upper-case letter to the corresponding
lower-case letter.  The argument must be representable as an unsigned char or
the value of EOF.
If the argument is an upper-case letter, the tolower() function
returns the corresponding lower-case letter if there is one; otherwise, the
argument is returned unchanged.*/

int	ft_tolower(int c)
{
	if ('A' <= c && c <= 'Z')
		return (c + 32);
	else
		return (c);
}

// int main()
// {
// 	printf("tolower\n");
// 	char c = 'X';
// 	printf("%d\n%d\n", c, ft_tolower(c));
// 	if (ft_tolower(c) == tolower(c))
// 		printf("Ok!");
// 	else
// 		printf("NOT OK!");
// 	return (0);
// }
