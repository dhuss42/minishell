#include <unistd.h>
#include "minishell_eichhoernchen.h"

void pwd()
{
    char *pathname;

    pathname = getcwd(NULL, 0);
    if (pathname != NULL)
    {
        ft_printf("%s\n", pathname);
        free(pathname);
    }
    else
        perror("pwd error: \n");
}

/* int main()
{
    pwd();
    return (0);
} */