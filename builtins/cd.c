/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:07:34 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/30 14:07:34 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell_eichhoernchen.h"

int		ft_cd(t_command *row)
{
    // add cd no args
    // default to HOME
    //  check for errors if HOME is not set
    if (row->args[1])
    {
        if (chdir(row->args[1]) == -1)
        {
            //print_error(errno, row->args[1], PRINT); // bash: cd: la: No such file or directory
            ft_printf("minishell: cd: %s: No such file or directory\n", row->args[1]);
            return (-1);
        }
    }
    // check for cd -
    //  moves to OLDPWD
    //  check for errors
    //  print the path

    // update oldpwd
    // update PWD



//a

    return (0);
}