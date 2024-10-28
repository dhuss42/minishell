
#include "../minishell_eichhoernchen.h"

void    ft_echo(t_shell *shell, t_command *row)
{
    bool newline;

    shell->i++;
    if (row->args[shell->i] == NULL)
    {
        printf("\n");
        return ;
    }
    if (ft_strncmp(row->args[shell->i], "-n", ft_strlen(row->args[shell->i])) == 0)
    {
        newline = false;
        while (row->args[shell->i] != NULL && ft_strncmp(row->args[shell->i], "-n", ft_strlen(row->args[shell->i])) == 0)
            shell->i++;
    }
    else
        newline = true;
    while (row->args[shell->i] != NULL)
    {
        ft_printf("%s", row->args[shell->i]);
        if (row->args[shell->i + 1] != NULL)
            ft_printf(" ");
        shell->i++;
    }
    if (newline == true)
        ft_printf("\n");
    return ;
}

// check for empty string
// if so print newline
// check if next argument is -n
// if so check in while loop if the following i arguments are also -n and skipp them
// printf everything until NULL
// print newline