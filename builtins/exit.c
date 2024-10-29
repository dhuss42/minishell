
#include "../minishell_eichhoernchen.h"

bool    is_numeric(char *str)
{
    size_t i;

    i = 0;
    while (str[i] != '\0')
    {
        if (!ft_isdigit(str[i]))
            return (false);
        i++;
    }
    return (true);
}

void    ft_exit(t_command *row)
{
    int exit_status;
    // exit_status = print_error(0, NULL, NOPRINT)

    exit_status = 0;
    if (row->args[1])
    {
        if (is_numeric(row->args[1]))
        {
            exit_status = ft_atoi(row->args[1]) % 256;
            // print_error(ft_atoi(row->args[1]) % 256, NULL, NOPRINT);
        }
        else
        {
            exit_status = 255;
            // print_error(255, NULL, NOPRINT); // exit: a: numeric argument required
        }
        if (row->args[2])
        {
            exit_status = 1;
            //print_error(255, NULL, NOPRINT); // bash: exit: too many arguments
        }
    }
    ft_printf("Exiting with status %d\n", exit_status);
    exit(exit_status);
}
