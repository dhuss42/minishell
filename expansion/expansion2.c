
#include "../minishell_eichhoernchen.h"

size_t  strlen_equal_2(char *str)
{
    size_t  i;

    i = 0;
    while (str[i] != '\0' && str[i] != '=')
        i++;
    return (i);
}

char    *compare_with_env_2(char *variable, char **env, char *exp)
{

    size_t  j = 0;

        while (env[j] != NULL)
        {   
            // printf("split_dollar: %s\n", split_dollar[i]);
            // printf("len: %zu\n", ft_strlen(split_dollar[i]));
            // printf("env: %s\n", env[j]);
            // printf("ft_len_equal: %zu\n", strlen_equal(env[j]));
            // printf("dif: %zu\n\n", ft_strlen(split_dollar[i]) - strlen_equal(env[j]));
            if (ft_strlen(variable) - strlen_equal_2(env[j]) == 0)
            {
                if (ft_strncmp(variable, env[j], strlen_equal_2(env[j])) == 0)
                {
                    return (exp = ft_substr(env[j], strlen_equal_2(env[j]) + 1, ft_strlen(env[j]) - strlen_equal_2(env[j]) - 1));
                }
            }
            j++;
        }
    return (exp); // no idea here
}

size_t  get_len_exp_2(t_command *row, char *exp, size_t *i)
{
    size_t  j;
    size_t  len;

    j = 0;
    len = 0;
    while(row->args[*i][j] != '\0' && row->args[*i][j] != '$') // not sure if the quotes should be counted at this step
    {
        len++;
        j++;
    }
    printf("row->args[*i] %s\n", row->args[*i]);
    printf("len: %zu\n", len);
    len += ft_strlen(exp);
    printf("len: %zu\n", len);
    return (len);
}

void    switcheroo_2(t_command *row, char *exp, size_t *i, size_t *k)
{
    size_t  len;
    size_t  j;
    size_t  iterate;
    size_t  index;
    char    *tmp;

    j = 0;
    iterate = 0;
    index = 0;
    // printf("TEST\n");
    len = get_len_exp_2(row, exp, i);
    printf("len: %zu\n", len);
    // printf("TEST1\n");
    tmp = malloc(sizeof(char) * (len + 1));
    if (!tmp)
        return ;
    // printf("TEST2\n");
    while(row->args[*i][j] != '\0' && row->args[*i][j] != '$')
        tmp[iterate++] = row->args[*i][j++];
    j++;
    while(row->args[*i][j] != '\0' && row->args[*i][j] != '$' && row->args[*i][j] != '\"' && row->args[*i][j] != '\'')
        j++;
    printf("before inserting expanded tmp: %s\n", tmp);
    printf("row->args[i]: %s\n", row->args[*i]);
    printf("row->args position[i]: %c\n", row->args[*i][j]);
    

    
    while (exp[index] != '\0')
        tmp[iterate++] = exp[index++];
    printf("after inserting expanded tmp: %s\n", tmp);
    printf("strlen: %zu\n", ft_strlen(tmp));
    *k = iterate;
    (*k)++;
    printf("k: %zu\n", *k);
    while (row->args[*i][j] != '\0')
        tmp[iterate++] = row->args[*i][j++];

    tmp[iterate] = '\0';
    printf("tmp: %s\n", tmp);
    // exit(EXIT_SUCCESS);

    // printf("before args[i]: %s\n", row->args[*i]);
    free(row->args[*i]);
    // printf("TESTHIER\n");
    row->args[*i] = ft_strdup(tmp);
    free(tmp);
}

void    get_expanded_2(char *variable, char **env, t_command *row, size_t *i, size_t *k)
{   
    // char    **split_dollar;
    char    *exp = NULL;
    // size_t  j = 0;

    variable++;
    printf("pos_dollar: %s\n", variable);

    exp = compare_with_env_2(variable, env, exp);
    printf("exp: %s\n", exp);

    switcheroo_2(row, exp, i, k); // reduce variables
    // clear_all(exp);
}