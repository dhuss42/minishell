#include <unistd.h>
#include "minishell_eichhoernchen.h"

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
