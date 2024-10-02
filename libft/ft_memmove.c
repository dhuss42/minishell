/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:49:02 by maustel           #+#    #+#             */
/*   Updated: 2023/10/10 17:45:04 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*this function copies len bytes from string src to string
 * dst. The two strings may overlap; the copy is always done in a non
 * destructive manner. The ft_memmove function returns the original value of
 * dst.*/

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*desti;
	char	*source;

	desti = (char *) dst;
	source = (char *) src;
	if (source < desti)
	{
		while (len > 0)
		{
			desti[len - 1] = source[len - 1];
			len --;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}

// int main()
// {
// 	printf("memmove\n");

// 	char src[] = "123456789";
// 	char *dst = src + 2;
// 	int len = 4;

// 	printf("%s\n", ft_memmove(dst, src, len));

// 	char src1[] = "123456789";
// 	char *dst1 = src1 + 2;

// 	printf("%s\n", memmove(dst1, src1, len));

// 	return (0);
// }
