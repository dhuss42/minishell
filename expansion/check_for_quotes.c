
#include "../minishell_eichhoernchen.h"


char    *tmp_dollar(t_command *row, size_t *i, size_t *k)
{
    size_t j;
    char    *tmp;

    printf("TEST3\n");
    tmp = NULL;
    (*k)++;
    j = *k;
    printf("in tmp_dollar row->args[*i]: %s\n", row->args[*i]);
    printf("len: %zu\n", ft_strlen(row->args[*i]));
    while (row->args[*i][j] != '\0' && row->args[*i][j] != '\"')
        j++;
    printf("TEST3.1\n");
    tmp = malloc(sizeof(char) * (j + 1));
    if (!tmp)
        return (NULL);
    j = 0;
    printf("TEST3.2\n");
    while (row->args[*i][*k] != '\0' && row->args[*i][*k] != '\"')
        tmp[j++] = row->args[*i][(*k)++];
    tmp[j] = '\0';

    printf("TEST3.3\n");
    if (row->args[*i][*k] == '\"')
        (*k)++;
    printf("tmp_dollar: %s\n", tmp);
    return (tmp);
}

bool    contains_dollar(char *str, size_t i)
{
    i++;
    while (str[i] != '\0' && str[i] != '\"')
    {
        if (str[i] == '$')
            return (true);
        i++;
    }
    return (false);
}

void    which_quotes(t_command *row, size_t *i, char **env)
{
    size_t  k;
    char    *tmp;

    k = 0;
    size_t round = 0;
    tmp = NULL;
    printf("TEST2\n");
    while (row->args[*i][k] != '\0')
    {
        printf("TEST21\n");
        printf("row->args[*i]: %s\n", row->args[*i]);
        printf("current char: %c \n", row->args[*i][k]);
        if (row->args[*i][k] == '\"' && contains_dollar(row->args[*i], k))
        {
            printf(MAGENTA"round [%zu]\n"WHITE, round++);
            // printf("k if: [%zu]\n", k);
            while (row->args[*i][k] != '\0' && row->args[*i][k] != '$')
                k++;
            tmp = tmp_dollar(row, i, &k);
            // printf("tmp_dollar: {%s}\n", tmp);
            get_expanded_2(tmp, env, row, i, &k);
            printf("after get_expanded row->args[*i]: %s\n", row->args[*i]);
            printf("TEST18\n");
            if (tmp)
            {
                printf("TEST19\n");
                printf(YELLOW"address tmp in which_quotes: %p\n"WHITE, tmp);
                free(tmp);
                printf("TEST19.1\n");
                tmp = NULL;
            }
        }
        else
        {
            printf("TEST20\n");
            k++;
        }
    }
}

// not checking for a dollar inside the quotes!! so exp is NULL when there is no dollar!

bool    check_for_quotes(t_list *table, char **env)
{
    t_list      *tmp;
    t_command   *row;
    size_t      i;

    tmp = table;
    while (tmp != NULL)
    {
        row = (t_command*)tmp->content;
        i = 0;
        while (row->args[i] != NULL)
        {
            // printf("TEST\n");
            which_quotes(row, &i, env);
            i++;
        }
        tmp = tmp->next;
    }
    return (true); // change
}

// ---- quote handling --- //
// char quotes
// go through the string and check if there are quotes
//      if there are quotes save quote symbol
//      find end of quote
//      call expansion if " "; but only expand what is inside the quote
//          call with $PATH if "$PATH"
//      move on

// --- expansion inside quote ---- //
//
//      get /usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/sbin
//      copy current content of args until first occurance of $ + the passed content inside the quote (strncmp)
//      replace first occurance of $ + the passed content inside the quote with /usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/sbin
//      copy remaining string 
//
// --- quote removal ---- //
// char quote
// get_len of string with quotes theoretically removed
// go through string and check for quotes
//      copy into 2nd string
//      if there is a quote save symbol
//          don't copy quote symbol
//          copy content between quotes up to closing
//          don't copy closing quote


// ---- test cases ----- //
//"$PATH"
// --> beginning of quote is copied due to how the expansion handles chars before the dollar sign
// --> /-- solved --/
//"$PATH""$HOME"
// --> only $PATH is expanded
// -- > /-- solved --/
// !!"$HOME"!!"$PATH"!!
// --> issue at test14, test3, and test 19
// --> // -- solved get_len_exp was not counting total len -- //
//"$$PATH"
// --> issue
// --> idea might need to check next char for is_alnum
// --> /--- solved ----/
//"$PATH$"
// --> issue creates tmp_dollar PATH$ does not find matching env and returns nullterminated string
//"$PATH$HOME$"
//"$PATH$HOME$$?"
//"$PATH$$$HOME"
//"$?$PATH$$$HOME$?"
//"$$$PATH$$$HOME$$"
//"PATH"
//"$"
// --> returns empty string
//"hallo"
// -->works
//"aaaaa$PATH"
// --> works
//"$PATHaaaaa"
// --> works (included ft_bzero when there is no matching env found)
//"$PATHaaaaa" "$HOME"
// --> works bzero solved iterater problem where args[i] is NULL but the args[i + 1] contains a string