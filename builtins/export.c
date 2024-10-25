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

int    key_exists(char **env, char *key)
{
    size_t  i;

    i = 0;
    while(env[i] != NULL)
    {
        if (ft_strncmp(key, env[i], strlen_equal(env[i])) == 0)
            return (i);
        i++;
    }
    return (-1);
}

size_t  get_len_new_env(char **env, t_command *row, size_t i)
{
    size_t count;

    count = 0;
    while (env[count] != NULL)
        count++;
    // printf(YELLOW"count after env: %zu\n"WHITE, count);
    while (row->args[i] != NULL)
    {
        // printf(BLUE"current_var %s\n"WHITE, row->args[i]);
        if (has_equal(row->args[i]) && valid_key_name(row->args[i]) && !key_exists(env, row->args[i]))
        {
            // printf(GREEN"export count: %zu\n"WHITE, count);
            count++;
        }
        i++;
    }
    // printf(YELLOW"count total: %zu\n"WHITE, count);
    return (count);
}

int    replace_key(t_shell *shell, t_command *row, size_t index, size_t j)
{
    printf(MAGENTA"replacing: %s at [%zu] in env with %s at [%zu] in args \n", shell->env[index], index, row->args[j], j);
    printf(MAGENTA"[%zu]row->args: %s\n"WHITE, j, row->args[j]);
    // shell->k = key_exists(shell->env, row->args[shell->i]);
    // printf(MAGENTA"[%zu]shell->k\n"WHITE, shell->k);
    shell->env[index] = ft_strdup(row->args[j]);
    if (!shell->env[index])
    {
        //print_error()
        return (-1);
    }
    printf(CYAN"[%zu] ENV shell->env: %s\n"WHITE, index, shell->env[index]);
    return (0);
}

char    **copy_new_envs(char **tmp, t_shell *shell, t_command *row)
{
    shell->j = 0;
    // printf("TEST2\n");
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
    // dups the environment variables into tmp
    while (row->args[shell->i] != NULL)
    {
        // printf(BLUE"current_var %s\n"WHITE, row->args[shell->i]);
        if (has_equal(row->args[shell->i]) && valid_key_name(row->args[shell->i]) && !key_exists(tmp, row->args[shell->i]))
        {
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
    // dups the remaining variables into tmp;
    // this needs a check if it lready exists (if yes then skip it in args)
    return (tmp);
}

int    check_duplicate_keys(t_shell *shell, t_command *row)
{
    size_t i;

    i = 0;
    while(row->args[i] != NULL)
    {
        printf("run [%zu]\n", i);
        if (key_exists(shell->env, row->args[i]) != -1)
        {
            if (replace_key(shell, row, key_exists(shell->env, row->args[i]), i) == -1)
                return (-1);
            // printf("TEST1\n");
        }
        i++;
    }
    return (0);
}

// go through args and call key_exists
// if the key exists change it in the env
// then go through the envs and copy them into tmp
// when appending the new variable
// --> check if the current new variable already exists in the tmp
// --> if so skip it
// --> if not copy it

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
    printf(BLUE"len: %zu\n"WHITE, shell->len);
    // gets length
    tmp = malloc(sizeof(char *) * (shell->len + 1));
    if (!tmp)
    {
    //  print_error(errno, NULL);
        return (-1);
    }
    // allocates

    if (check_duplicate_keys(shell, row) == -1)
        return (-1);
    // checks for duplicate keys and replaces in shell->env
    tmp = copy_new_envs(tmp, shell, row);
    if (!tmp)
        return (-1);
    // copies the environemtn variables old and new

    if (shell->env)
        clear_all(shell->env);
    // printf("TEST1\n");
    if (copy_env(tmp, shell) == -1)
        return (clear_all(shell->env), clear_all(tmp), -1); //not sure about clearing env
    // printf("TEST2\n");
    // printf(YELLOW"adress tmp %p\n"WHITE, tmp);
    // printf(YELLOW"adress env %p\n"WHITE, shell->env);
    // if (tmp)
    //     clear_all(tmp);
    // printf("TEST3\n");
    return (0);
}
