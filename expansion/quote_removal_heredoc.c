
#include "../minishell.h"

// get len of the string without the quotes
// calloc with new len
// copy without quotes
// dup and free

char    *remove_quotes_loop_hd(char *str, char *no_quotes)
{
    int     i;
    int     j;
    char    quote;

    i = 0;
    j = 0;
    while (str[i] != '\0')
    {
        if (is_quotes(str[i]))
        {
            quote = str[i];
            i++;
            while (str[i] != '\0' && str[i] != quote)
                no_quotes[j++] = str[i++];
            i++;
        }
        else
            no_quotes[j++] = str[i++];
    }
    return (no_quotes);
}

int get_len_nq_heredoc(char *str)
{
    int     len;
    int     i;
    char    quote;

    i = 0;
    len = 0;
    while (str[i] != '\0')
    {
        if (is_quotes(str[i]))
        {
            quote = str[i];
            i++;
            while (str[i] != '\0' && str[i] != quote)
            {
                len++;
                i++;
            }
            i++;
        }
        else
        {
            len++;
            i++;
        }
    }
    return (len);
}

char *quote_heredoc(char *str)
{
    char    *no_quotes;
    int     len;
    
    len = get_len_nq_heredoc(str);
    // printf(YELLOW"len: %d\n"WHITE, len);
    no_quotes = safe_ft_calloc(len + 1, sizeof(char));
    if (!no_quotes)
        return (NULL);
    no_quotes = remove_quotes_loop_hd(str, no_quotes);
    
    // printf(BLUE"no_quotes: %s\n"WHITE, no_quotes);
    return (no_quotes); // needs to be freed at some point
}
