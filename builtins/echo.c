
#include "../minishell_eichhoernchen.h"

bool    is_only_n(char *str)
{
    size_t  i;

    i = 0;
    if (str[i] == '-')
        i++;
    else
        return (false);
    while (str[i] == 'n')
        i++;
    if (str[i] == '\0')
        return (true);
    else
        return (false);
}

void    ft_echo(t_shell *shell, t_command *row)
{
    bool newline;

    shell->i++;
    if (row->args[shell->i] == NULL)
    {
        ft_printf("\n");
        return ;
    }
    if (is_only_n(row->args[shell->i]))
    {
        newline = false;
        while (row->args[shell->i] != NULL && is_only_n(row->args[shell->i]))
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
// check if next argument is -n or -nnnnnnnn
// if so check in while loop if the following i arguments are also -n or -nnnnn and skipp them
// printf everything until NULL
// print newline if true