
#include "../minishell_eichhoernchen.h"


// void    check_for_quotes()
// {

// }


size_t  strlen_equal(char *str)
{
    size_t  i;

    i = 0;
    while (str[i] != '\0' && str[i] != '=')
        i++;
    return (i);
}

char    **compare_with_env(char **split_dollar, char **env, char **exp)
{
    size_t  i = 0;
    size_t  j = 0;
    size_t  k = 0;

    while (split_dollar[i] != NULL)
    {
        j = 0;
        while (env[j] != NULL)
        {   
            // printf("split_dollar: %s\n", split_dollar[i]);
            // printf("len: %zu\n", ft_strlen(split_dollar[i]));
            // printf("env: %s\n", env[j]);
            // printf("ft_len_equal: %zu\n", strlen_equal(env[j]));
            // printf("dif: %zu\n\n", ft_strlen(split_dollar[i]) - strlen_equal(env[j]));
            if (ft_strlen(split_dollar[i]) - strlen_equal(env[j]) == 0)
            {
                if (ft_strncmp(split_dollar[i], env[j], strlen_equal(env[j])) == 0)
                {
                    exp[k] = ft_substr(env[j], strlen_equal(env[j]) + 1, ft_strlen(env[j]) - strlen_equal(env[j]) - 1);
                    k++;
                }
            }
            j++;
        }
        i++;
    }
    exp[k] = NULL;
    return (exp);
}

size_t  get_len_exp(t_command *row, char **exp, size_t *i)
{
    size_t  j;
    size_t  len;

    j = 0;
    len = 0;
    while(row->args[*i][j] != '\0' && row->args[*i][j] != '$')
    {
        len++;
        j++;
    }
    printf("len: %zu\n", len);
    j = 0;
    while (exp[j] != NULL)
    {
        len += ft_strlen(exp[j]);
        j++;
    }
    printf("len: %zu\n", len);
    return (len);
}

void    switcheroo(t_command *row, char **exp, size_t *i)
{
    size_t  len;
    size_t  j;
    size_t  k;
    size_t  index;
    char    *tmp;

    j = 0;
    k = 0;
    index = 0;
    len = get_len_exp(row, exp, i);
    tmp = malloc(sizeof(char) * (len + 1));
    if (!tmp)
        return ;
    while(row->args[*i][j] != '\0' && row->args[*i][j] != '$')
        tmp[k++] = row->args[*i][j++];
    j = 0;
    // printf("tmp: %s\n", tmp);
    while (exp[j] != NULL)
    {
        // printf("TEST\n");
        index = 0;
        while (exp[j][index] != '\0')
        {
            // printf("tmp: %s\n", tmp);
            tmp[k++] = exp[j][index++];
        }
        j++;
    }
    // printf("tmp: %s\n", tmp);
    tmp[k] = '\0';
    // printf("before args[i]: %s\n", row->args[*i]);
    free(row->args[*i]);
    row->args[*i] = ft_strdup(tmp);
    free(tmp);
}

void    get_expanded(char *pos_dollar, char **env, t_command *row, size_t *i)
{   
    char    **split_dollar;
    char    **exp = NULL;
    size_t  j = 0;

    split_dollar = ft_split(pos_dollar, '$');
    while(split_dollar[j] != NULL)
        j++;
    // printf("j : %zu\n", j);
    exp = malloc(sizeof(char *) * j + 1);
    if (!exp)
        return ;
    exp = compare_with_env(split_dollar, env, exp);
    clear_all(split_dollar);
    j = 0;
    while (exp[j] != NULL)
    {
        // printf("\033[32m[%zu] expanded: %s\033[0m\n", j, exp[j]);
        j++;
    }
    // printf("row->args: %s\n", row->args[*i]);
    // printf("i: %zu\n", *i);
    switcheroo(row, exp, i);
    clear_all(exp);
}

void    check_for_dollar(t_list *table, char **env)
{
    t_list      *tmp;
    size_t      i;
    t_command   *row;
    char        *pos_dollar;

    tmp = table;
    while (tmp != NULL)
    {
        row = (t_command*) tmp->content;
        i = 0;
        while(row->args[i] != NULL)
        {
            // printf("[%zu] row->args: %s\n", i, row->args[i]);
            pos_dollar = ft_strchr(row->args[i], '$');
            if (pos_dollar != NULL)
                get_expanded(pos_dollar, env, row, &i);

            // change to env content and leave if its only $
            i++;
        }
        tmp = tmp->next;
    }
    print_table(table);
}


t_list *expansion(t_list *table, char **env) // change to our env
{
    // check_for_quotes();
    check_for_dollar(table, env);
    return (NULL);
}

//problem: currently not expanding $PATH after | in [echo $HOME|$PATH]
// --> solved i was not reseting to 0 in loop

//problem: last $ is disappearing in [$HOME$PATH$]
// same problem with $?
// also in isolation $ and $? disappear because of split

//