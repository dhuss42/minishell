/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:04:25 by dhuss             #+#    #+#             */
/*   Updated: 2024/09/09 13:00:19 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
char	*ft_strchr_gnl(const char *s, int c);
char	*ft_strdup_gnl(const char *s1);
char	*ft_strjoin_gnl(char const *s1, char const *s2);
void	*ft_calloc_gnl(size_t count, size_t size);
size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize);

#endif
