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

void    export(char **env, char *first_var, ...)
{
    va_list args;
    size_t count;
    size_t  i;
    char   **tmp;

    count = 0;
    i = 0;
    const char *current_var;

    if (first_var == NULL)
        return ;
    current_var = first_var;
    while (env[count] != NULL)
        count++;
    printf(YELLOW"count after env: %zu\n"WHITE, count);
    va_start(args, first_var);
    while (current_var != NULL)
    {
        printf(BLUE"current_var %s\n"WHITE, current_var);
        if (has_equal(current_var) && valid_key_name(current_var))
        {
            printf(GREEN"export count: %zu\n"WHITE, count);
            count++;
        }
        current_var = va_arg(args, const char*);
    }
    va_end(args);
    printf(YELLOW"count total: %zu\n"WHITE, count);

    tmp = malloc(sizeof(char *)*(count + 1));
    if (!tmp)
        return ;

    while (env[i] != NULL)
    {
        tmp[i] = ft_strdup(env[i]);
        if (!tmp[i])
            return ;
        i++;
    }

    current_var = first_var;
    va_start(args, first_var);
    while (current_var != NULL)
    {
        printf(BLUE"current_var %s\n"WHITE, current_var);
        if (has_equal(current_var) && valid_key_name(current_var))
        {
            printf(GREEN"export count: %zu\n"WHITE, count);
            tmp[i] = ft_strdup(current_var);
            if (!tmp[i])
                return ;
            i++;
        }
        current_var = va_arg(args, const char*);
    }
    va_end(args);
    // get len of env
    // get len of the variables following export
    //  len++ if the word contains an = and has valid chars before
    //      valid chars initial position: a-z, A-Z and _
    //      valid chars following initial: a-z, A-Z, 0-9, _,
    //      if no char before = then: bash: export: `=': not a valid identifier
    // allocate tmp ** with enough space for exported variables
    // copy env into tmp**
    // free env**
    // copy the exported variables into tmp (same principle as above)
    // strdup tmp into env
    // 
    // clear_all(env);
    env = tmp;
    ft_env(env);
    va_end(args);
}

int main(int argc, char *argv[], char **env)
{
    (void) argc;
    (void) argv;
    export(env, "VAR1111111=value1", "hallo=hallo", "22222222=value3", NULL);

    return 0;
}