/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:06:44 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/18 13:11:18 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

int	ft_pwd(void)
{
	char	*pathname;

	pathname = getcwd(NULL, 0);
	if (pathname)
	{
		ft_printf("%s\n", pathname);
		free(pathname);
		return (0);
	}
	else
		return (print_error(errno, NULL, PRINT));
}
