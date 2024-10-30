/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:06:44 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/30 14:07:01 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell_eichhoernchen.h"

int ft_pwd()
{
    char *pathname;

    pathname = getcwd(NULL, 0);
    if (pathname != NULL)
    {
        ft_printf("%s\n", pathname);
        free(pathname);
        return (0);
    }
    else
    {
        perror("pwd error: \n"); // call error function
        //  print_error(errno, NULL);
        return (-1);
    }
}
