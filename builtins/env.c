#include <unistd.h>
#include "minishell_eichhoernchen.h"

void    ft_env(char **env)
{
    size_t i;

    if (env == NULL)
        return ;
    i = 0;
    while (env[i] != NULL)
        printf("%s\n", env[i++]); // change to ft_printf
}

/* int main(int argc, char *argv[], char **env)
{
    (void) argc;
    (void) argv;
    ft_env(env);
    return (0);
} */