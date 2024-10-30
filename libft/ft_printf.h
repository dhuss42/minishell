/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:52:16 by dhuss             #+#    #+#             */
/*   Updated: 2024/09/17 12:37:45 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *str, ...);
void	ft_putchar(char c, int *counter);
void	ft_putstr(char *s, int *counter);
void	ft_putnbr(int n, int *counter);
void	ft_putnbr_unsigned(unsigned int n, int *counter);
void	ft_putnbr_base(unsigned int n, int *counter);
void	ft_putnbr_base_lowercase(unsigned int n, int *counter);
void	ft_putptr(void *ptr, int *counter);

#endif
