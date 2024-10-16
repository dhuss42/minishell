
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
    // printf("len: %zu\n", len);
    j = 0;
    while (exp[j] != NULL)
    {
        len += ft_strlen(exp[j]);
        j++;
    }
    // printf("len: %zu\n", len);
    return (len);
}

void    insert_dollar_front(char **tmp, char *front, size_t *k)
{
    size_t  i;

    i = 0;
    while (front[i] != '\0')
    {
        tmp[0][(*k)++] = front[i++];
    }
    printf("tmp front: %s\n", tmp[0]);
    free(front);
}

void    insert_dollar_back(char **tmp, char *back, size_t *k)
{
    size_t  i;

    i = 0;
    while (back[i] != '\0')
    {
        tmp[0][(*k)++] = back[i++];
    }
    printf("tmp back: %s\n", tmp[0]);
    free(back);
}

void    switcheroo(t_command *row, char **exp, size_t *i, char *front, char *back)
{
    size_t  len;
    size_t  j;
    size_t  k;
    size_t  index;
    char    *tmp;

    j = 0;
    k = 0;
    index = 0;
    printf("TEST\n");
    len = get_len_exp(row, exp, i);
    if (front != NULL)
        len += ft_strlen(front);
    if (back != NULL)
        len += ft_strlen(back);
    printf("TEST1\n");
    tmp = malloc(sizeof(char) * (len + 1));
    if (!tmp)
        return ;
    printf("TEST2\n");
    while(row->args[*i][j] != '\0' && row->args[*i][j] != '$')
        tmp[k++] = row->args[*i][j++];
    printf("TEST3\n");
    if (front != NULL)
        insert_dollar_front(&tmp, front, &k);
    j = 0;
    // printf("tmp: %s\n", tmp);
    while (exp[j] != NULL)
    {
        printf("TEST\n");
        index = 0;
        while (exp[j][index] != '\0')
        {
            // printf("tmp: %s\n", tmp);
            tmp[k++] = exp[j][index++];
        }
        j++;
    }
    printf("TEST66\n");
    if (back != NULL)
        insert_dollar_back(&tmp, back, &k);
    // printf("tmp: %s\n", tmp);
    tmp[k] = '\0';
    // printf("before args[i]: %s\n", row->args[*i]);
    free(row->args[*i]);
    row->args[*i] = ft_strdup(tmp);
    free(tmp);
}

char    *check_for_dollar_front(char *str, char *front, size_t *signal)
{
    size_t j;

    j = 0;
    while (str[j] != '\0' && !ft_isalnum(str[j + 1]))
        j++;
    if (str[j] == '\0')
        *signal = 0;
    front = malloc(sizeof(char) * (j + 1));
    if(!front)
        return (NULL);
    j = 0;
    while (str[j] != '\0' && !ft_isalnum(str[j + 1]))
    {
        front[j] = str[j];
        j++;
    }
    front[j] = '\0';
    printf("front: %s\n", front);
    return (front);
}

char    *check_for_dollar_back(char *str, char *back)
{
    size_t end;
    size_t start;
    size_t  i;

    end = 0;
    start = 0;
    i = 0;
    while (str[end] != '\0')
        end++;
    end--;
    start = end;
    while(!ft_isalnum(str[start]) && start > 0)
        start--;
    start++;
    printf("start: %zu\n", start);
    printf("end: %zu\n", end);
    back = malloc(sizeof(char) * (end - start + 2));
    if (!back)
        return (NULL);
    while (str[start] != '\0')
    {
        back[i++] = str[start++];
    }
    back[i] = '\0';
    printf("back: %s\n", back);
    return (back);
}

void    get_expanded(char *pos_dollar, char **env, t_command *row, size_t *i)
{   
    char    **split_dollar;
    char    **exp = NULL;
    char    *front = NULL;
    char    *back = NULL;
    size_t  j = 0;
    size_t  signal = 1;

    front = check_for_dollar_front(pos_dollar, front, &signal);
    // problem of doubling string when only $$$
    if (signal == 1)
        back = check_for_dollar_back(pos_dollar, back);
    // build a check that checks if there are dollar signs without al_num and dollar signs with ? before the variables and after
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
    switcheroo(row, exp, i, front, back); // reduce variables
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
            pos_dollar = ft_strchr(row->args[i], '$');
            if (pos_dollar != NULL)
                get_expanded(pos_dollar, env, row, &i);
            i++;
        }
        tmp = tmp->next;
    }
    // print_table(table);
}


t_list *expansion(t_list *table, char **env) // change to our env
{
    check_for_quotes(table, env); // cif there are no quotes go into check_for_dollar
    // exit(EXIT_SUCCESS);
    check_for_dollar(table, env); 
    print_table(table);
    return (NULL);
}




// strange thing happes with aösdökd$öaksd
// --> don't have an anwser for it

// potential problem with $$HOME$$$PATH
// --> depends on how we are handling $$
// ---- solving ----
// instead of splitting with $ I could insert a ws before every $ and slpit with space
// then check if with ft_isalnum if the string in question is a variable or $ or $?
// if alnum remove the $ and compare with the envs

// potential problem with non existing variables such as $TEST
//  now in args** there are empty string stored
//  don't know if that is an issue or if the indexes need to be arranged properly again
// example bash: echo hallo $TEST $sa hallo"welt   "hallo
//       --> hallo hallowelt   hallo