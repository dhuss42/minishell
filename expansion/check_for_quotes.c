
#include "../minishell_eichhoernchen.h"


char    *tmp_dollar(t_command *row, size_t *i, size_t *k)
{
    size_t j;
    char    *tmp;

    (*k)++;
    j = *k;
    while (row->args[*i][j] != '\0' && row->args[*i][j] != '\"')
        j++;
    tmp = malloc(sizeof(char) * (j + 1));
    if (!tmp)
        return (NULL);
    j = 0;
    while (row->args[*i][*k] != '\0' && row->args[*i][*k] != '\"')
        tmp[j++] = row->args[*i][(*k)++];
    tmp[j] = '\0';
    if (row->args[*i][*k] == '\"')
        (*k)++;
    printf("tmp_dollar: %s\n", tmp);
    return (tmp);
}

void    which_quotes(t_command *row, size_t *i, char **env)
{
    size_t  k;
    char    *tmp;

    k = 0;
    while (row->args[*i][k] != '\0')
    {
        if (row->args[*i][k] == '\"')
        {
            printf("k if: [%zu]\n", k);
            tmp = tmp_dollar(row, i, &k);
            printf("tmp_dollar: {%s}\n", tmp);
            get_expanded_2(tmp, env, row, i, &k);
            if (tmp)
                free(tmp);
            // k needs to be incremented by the len of the variable content
        }
        else
        {
            printf("k else: [%zu]\n", k);
            k++;
        }
    }
}

bool    check_for_quotes(t_list *table, char **env)
{
    t_list      *tmp;
    t_command   *row;
    size_t      i;

    tmp = table;
    (void) env;
    while (tmp != NULL)
    {
        row = (t_command*)tmp->content;
        i = 0;
        while (row->args[i] != NULL)
        {
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
//"$PATH""$HOME"
// --> only $PATH is expanded
//"$$PATH"
//"$PATH$"
//"$PATH$HOME$"
//"$PATH$HOME$$?"
//"$PATH$$$HOME"
//"$?$PATH$$$HOME$?"
//"$$$PATH$$$HOME$$"