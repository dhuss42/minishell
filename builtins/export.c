// syntax from export is:
// export VAR_NAME=value
// export VAR_NAME=value VAR_NAME1=value1 VAR_NAME2=value2

#include "../minishell_eichhoernchen.h"

bool    has_equal(const char *str)
{
    size_t i;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '=')
            return (true);
        i++;
    }
    return (false);
}

bool    valid_key_name(const char *str)
{
    size_t i;

    i = 0;
    if (!ft_isalpha(str[i]) && str[i] != '_')
        return (false);
    i++;
    while (str[i] != '\0' && str[i] != '=')
    {
        if (!(ft_isalnum(str[i]) || str[i] == '_'))
            return (false);
        i++;
    }
    return (true);
}

size_t  get_len_new_env(char **env, t_command *row, size_t i)
{
    size_t count;

    count = 0;
    while (env[count] != NULL)
        count++;
    printf(YELLOW"count after env: %zu\n"WHITE, count);
    while (row->args[i] != NULL)
    {
        printf(BLUE"current_var %s\n"WHITE, row->args[i]);
        if (has_equal(row->args[i]) && valid_key_name(row->args[i]))
        {
            printf(GREEN"export count: %zu\n"WHITE, count);
            count++;
        }
        i++;
    }
    printf(YELLOW"count total: %zu\n"WHITE, count);
    return (count);
}

char    **copy_new_envs(char **tmp, t_shell *shell, t_command *row)
{
    shell->j = 0;
    while (shell->env[shell->j] != NULL)
    {
        tmp[shell->j] = ft_strdup(shell->env[shell->j]);
        if (!tmp[shell->j])
        {
            clear_all(tmp);
            //  print_error(errno, NULL);
            return (NULL);
        }
        shell->j++;
    }
    while (row->args[shell->i] != NULL)
    {
        printf(BLUE"current_var %s\n"WHITE, row->args[shell->i]);
        if (has_equal(row->args[shell->i]) && valid_key_name(row->args[shell->i]))
        {
            printf(GREEN"export count: %zu\n"WHITE, shell->i);
            tmp[shell->j] = ft_strdup(row->args[shell->i]);
            if (!tmp[shell->j])
            {
                clear_all(tmp);
                //  print_error(errno, NULL);
                return (NULL);
            }
            shell->j++;
        }
        shell->i++;
    }
    tmp[shell->j] = NULL;
    return (tmp);
}

int    ft_export(t_shell *shell, t_command *row)
{
    char   **tmp;

    tmp = NULL;
    shell->i++;
    if (row->args[shell->i] == NULL)
    {
        // not sure what error str is empty?
        return (-1);
    }
    shell->len = get_len_new_env(shell->env, row, shell->i);
    tmp = malloc(sizeof(char *) * (shell->len + 1));
    if (!tmp)
    {
    //  print_error(errno, NULL);
        return (-1);
    }
    tmp = copy_new_envs(tmp, shell, row);
    if (!tmp)
        return (-1);
    if (shell->env)
        clear_all(shell->env);
    copy_env(tmp, shell); // error handling
    if (tmp)
        clear_all(tmp);
    return (0);
}

// still have to handle overwriting of a key
// inhibitor on duplicates