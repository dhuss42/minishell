

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



    return (0);
}