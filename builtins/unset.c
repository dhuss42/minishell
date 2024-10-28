
#include "../minishell_eichhoernchen.h"

// can take multiple args
// check if key exists 
// if not return 

// get length of tmp double char*
// if key exists skip in counter

// go through the envs and copy them into a tmp double char**
// if existing key is found
// skip it

// duplicate tmp double char ** into shell->env

void get_len_unset(t_shell *shell, t_command *row)
{
    size_t j;
    size_t k;
    size_t counter;

    counter = 0;
    k = shell->i;
    while (row->args[k] != NULL)
    {
        j = 0;
        while (shell->env[j] != NULL)
        {
            if (ft_strncmp(row->args[k], shell->env[j], strlen_equal(shell->env[j])) == 0)
            {
                printf(GREEN"increasing counter\n"WHITE);
                counter++;
            }
            j++;
        }
        k++;
    }
    shell->len = j - counter;
}

int ft_unset(t_shell *shell, t_command *row)
{
    char    **tmp;
    size_t  j;
    size_t  k;

    get_len_unset(shell, row);
    printf("shell->len: %zu\n", shell->len);
    tmp = malloc(sizeof(char *) * (shell->len + 1));
    if (!tmp)
    {
        //call error
        return (-1);
    }
    j = 0;
    k = 0;
    printf("TEST\n");
    while (row->args[shell->i] != NULL)
    {
        while (shell->env[k] != NULL)
        {
            if (ft_strncmp(row->args[shell->i], shell->env[k], strlen_equal(shell->env[k])) != 0)
            {
                tmp[j] = ft_strdup(shell->env[k]);
                if (!tmp[j])
                {
                    clear_all(tmp);
                    return (-1);
                }
                j++;
            }
            k++;
        }
        shell->i++;
    }
    if (shell->env)
        clear_all(shell->env);
    copy_env(tmp, shell);
    if (!shell->env)
        return (-1);
    if (tmp)
        clear_all(tmp);
    return (0);
}

// not working at the moment