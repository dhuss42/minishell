/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:03:47 by dhuss             #+#    #+#             */
/*   Updated: 2024/09/09 13:00:00 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = (unsigned char *)b;
	while (i < len)
	{
		ptr[i] = c;
		i++;
	}
	return (ptr);
}

static char	*separate_two(char *remainder)
{
	char	*new_remainder;
	char	*line;
	ssize_t	len;

	new_remainder = ft_strchr_gnl(remainder, '\n');
	len = new_remainder - remainder;
	line = ft_calloc_gnl(len + 2, sizeof(char));
	if (!line)
		return (NULL);
	if (new_remainder != NULL)
	{
		ft_strlcpy_gnl(line, remainder, len +2);
		ft_strlcpy_gnl(remainder, new_remainder + 1, BUFFER_SIZE);
	}
	return (line);
}

static char	*separate(char *joined_s, char *remainder)
{
	char	*line;
	char	*new_remainder;
	ssize_t	len;

	line = ft_strdup_gnl(joined_s);
	if (!line)
		return (NULL);
	new_remainder = ft_strchr_gnl(joined_s, '\n');
	if (new_remainder != NULL)
	{
		len = new_remainder - joined_s;
		ft_strlcpy_gnl(line, joined_s, len +2);
		ft_strlcpy_gnl(remainder, new_remainder + 1, BUFFER_SIZE);
	}
	if (joined_s != remainder)
		free(joined_s);
	return (line);
}

static char	*ft_read(char *remainder, int fd, char *buffer, int *r)
{
	ssize_t	bytes_read;
	char	*joined;
	char	*line;
	char	*tmp;

	joined = remainder;
	while (ft_strchr_gnl(joined, '\n') == NULL)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (remainder[0] == 0 && bytes_read <= 0 && joined[bytes_read] == '\0')
			return (NULL);
		if (bytes_read <= 0)
		{
			*r = bytes_read;
			break ;
		}
		buffer[bytes_read] = '\0';
		tmp = joined;
		joined = ft_strjoin_gnl(joined, buffer);
		if (tmp != remainder)
			free (tmp);
	}
	line = separate(joined, remainder);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	remainder[BUFFER_SIZE +1];
	char		*buffer;
	char		*next_line;
	int			r;

	r = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		ft_memset(remainder, 0, sizeof(remainder));
		return (NULL);
	}
	buffer = ft_calloc_gnl(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	if (ft_strchr_gnl(remainder, '\n') == NULL)
		next_line = ft_read(&remainder[0], fd, buffer, &r);
	else
		next_line = separate_two(remainder);
	if (r <= 0 && remainder[0] == 0 && next_line[r] == '\0')
		return (free(buffer), NULL);
	if (r <= 0)
		ft_memset(remainder, 0, sizeof(remainder));
	return (free(buffer), next_line);
}
