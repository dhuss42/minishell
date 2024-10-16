
#include "../minishell_eichhoernchen.h"

void    which_quotes(t_command *row)
{
    size_t i;
    char    quote;

    i = 0;
    quote = '\0';
    while (row->args[i] != '\0')
    {
        if (row->args[i] == '\"' || row->args[i] == )
    }
}

bool    check_for_quotes(t_list *table, char **env)
{
    t_list      *tmp;
    t_command   *row;
    size_t      i;

    tmp = table;
    i = 0;
    while (tmp != NULL)
    {
        row = (t_command*)tmp->content;
        while (row->args[i] != NULL)
        {

            i++;
        }
        tmp = tmp->next;
    }
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
