/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:04:22 by dhuss             #+#    #+#             */
/*   Updated: 2024/09/09 13:00:00 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr_gnl(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != (char) c)
	{
		if (s[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *) &s[i]);
}

char	*ft_strdup_gnl(const char *s1)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = 0;
	while (s1[i] != '\0')
		i++;
	ptr = (char *) malloc (i + 1);
	if (ptr == NULL)
		return (NULL);
	j = 0;
	while (j < i)
	{
		ptr[j] = s1[j];
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	size_t	i;
	size_t	total_len;
	char	*new_string;

	total_len = 0;
	while (s1[total_len])
		total_len++;
	i = 0;
	while (s2[i])
		i++;
	total_len = total_len + i;
	new_string = (char *)malloc(total_len + 1);
	if (new_string == NULL)
		return (NULL);
	i = 0;
	while (*s1)
		new_string[i++] = *s1++;
	while (*s2)
		new_string[i++] = *s2++;
	new_string[i] = '\0';
	return (new_string);
}

void	*ft_calloc_gnl(size_t count, size_t size)
{
	size_t			total_size;
	size_t			i;
	void			*ptr;
	unsigned char	*fill;

	total_size = count * size;
	i = 0;
	ptr = malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	fill = (unsigned char *) ptr;
	while (i < total_size)
	{
		fill[i] = 0;
		i++;
	}
	return (ptr);
}

size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (dstsize != '\0')
	{
		while (dstsize > 1 && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
			dstsize--;
		}
		dst[i] = '\0';
	}
	while (src[j] != '\0')
		j++;
	return (j);
}
