

#include "minishell_eichhoernchen.h"

t_command   *create_cmd_block(void)
{
    t_command   *new_cmd;

    new_cmd = NULL;
    new_cmd = malloc(sizeof(t_command));
    if (!new_cmd)
        return (NULL);
    new_cmd->args = NULL;
    new_cmd->filename = NULL;
    new_cmd->red_symbol = NULL;
    return (new_cmd);
}

int is_redirection(token *current_token)
{
    if (current_token->type == TOKEN_REDIN || current_token->type == TOKEN_REDOUT 
        || current_token->type == TOKEN_REDAPPEND || current_token->type == TOKEN_HEREDOC)
        return (1);
    else
        return (0);
}

int is_filename(token *current_token)
{
    if (current_token->type == TOKEN_WORD || current_token->type == TOKEN_SQUOTES 
        || current_token->type == TOKEN_DQUOTES || current_token->type == TOKEN_ARGS
            || current_token->type == TOKEN_EXITSTATUS) // if you type > $? it creates a file with the last exit status
        return (1);
    else
        return (0);
}

size_t  count_lines_table(t_list *token_list)
{
    t_list  *tmp;
    size_t  lines;
    token   *current_token;

    tmp = token_list;
    lines = 0;
    while(tmp != NULL)
    {
        current_token = (token *)tmp->content;
        if (current_token->type == TOKEN_PIPE)
            lines++;
        tmp = tmp->next;
    }
    return (lines + 1);
}

void    nbr_words_redirections(size_t *words, size_t *red, t_list **token_list, size_t *filename)
{
    t_list  *tmp;
    token   *current_token;

    tmp = *token_list;
    *words = 0;
    *red = 0;
    *filename = 0;
    while (tmp != NULL)
    {
        current_token = (token *)tmp->content;
        if (current_token->type == TOKEN_PIPE)
            break ;
        if (is_redirection(current_token))
        {
            (*red)++;
            if (tmp->next != NULL)
            {
                (*filename)++;
                tmp = tmp->next;
            }
        }
        else
            (*words)++;
        tmp = tmp->next;
    }
    *token_list = tmp;
}

t_command   *populate_cmd(t_command *new_cmd, t_list *tl_pos)
{
    token   *current_token;
    token   *next_token;
    t_list  *tmp;
    size_t  i;
    size_t  j;

    i = 0;
    j = 0;
    tmp = tl_pos;
    while(tmp != NULL)
    {
        current_token = (token *)tmp->content;
        if (tmp->next != NULL)
            next_token = (token *)tmp->next->content; //in case of an incorrect input > >
        if (current_token->type == TOKEN_PIPE)
            break ;

        if (is_redirection(current_token))
        {
            new_cmd->red_symbol[i] = malloc(sizeof(char) * (ft_strlen(current_token->input) + 1));
            if (!new_cmd->red_symbol[i])
                return (NULL); // free everything
            ft_strlcpy(new_cmd->red_symbol[i], current_token->input, ft_strlen(current_token->input) + 1);
            printf("REDIRECTION: [%s]\n", new_cmd->red_symbol[i]);
            // this function checks if the current node is a redirection symbol and allocates enough memory for it in the struct(table)‚
            // copies the symbol in struct at index i (the same index as the filename later on)
            if (is_filename(next_token)) // not sure if I need to check for legit filename or if I should catch the error later on?
            {
                new_cmd->filename[i] = malloc(sizeof(char) * (ft_strlen(next_token->input) + 1)); // contine later 8.10 10:26
                if (!new_cmd->filename[i])
                    return (NULL); // free everything
                ft_strlcpy(new_cmd->filename[i], next_token->input, ft_strlen(next_token->input) + 1);
                printf("FILENAME: [%s]\n", new_cmd->filename[i]);
                tmp = tmp->next;
            }
            // this part checks if the next node in the list is a possible file name and allocates enough memory in the table for its name
            // the file name is saved at the same index as the redirection symbol
            // needs and additional itteration
            i++;
        }
        else 
        {
            new_cmd->args[j] = malloc(sizeof(char) * ft_strlen(current_token->input) + 1);
            if (!new_cmd->args[j])
                return (NULL); // free everything
            ft_strlcpy(new_cmd->args[j], current_token->input, ft_strlen(current_token->input) + 1);
            printf("ARGS: [%s]\n", new_cmd->args[j]);
            j++;
        }
        tmp = tmp->next;
    }
    new_cmd->args[j] = NULL;
    new_cmd->red_symbol[i] = NULL;
    new_cmd->filename[i] = NULL;
    return (new_cmd);
}

t_command   *allocate_cmd(t_command *new_cmd, t_list *tl_pos, size_t wc, size_t rc, size_t fc)
{
    new_cmd->args = malloc(sizeof(char *) * (wc + 1));
    if (!new_cmd->args)
        return (NULL);
    new_cmd->red_symbol = malloc(sizeof(char *) * (rc + 1));
    if (!new_cmd->red_symbol)
    {
        free(new_cmd->args);
        return (NULL);
    }
    new_cmd->filename = malloc (sizeof(char *) * (fc + 1));
    if (!new_cmd->filename) // what if we are in the second line of the table and have an error (free the remaining table)
    {
        free(new_cmd->args);
        free(new_cmd->red_symbol);
        return (NULL);
    }
    new_cmd = populate_cmd(new_cmd, tl_pos);
    
    return (new_cmd);
}

t_list  *create_table(t_list *token_list, t_list *table)
{
    t_list      *tmp;
    t_list      *tmp2;
    t_list      *new_node;
    t_command   *new_cmd;
    // token       *current_token;
    size_t      lines;
    size_t      nbr_words = 0;
    size_t      nbr_reds = 0;
    size_t      nbr_filenames = 0;

    // new_cmd = NULL;
    tmp = token_list;
    lines = count_lines_table(token_list);

    size_t i = 0;
    while (lines > 0 && tmp != NULL)
    {
        printf("[%zu]\n", i);
        new_cmd = create_cmd_block();
        new_node = ft_lstnew((void *)new_cmd);
        tmp2 = tmp;
        nbr_words_redirections(&nbr_words, &nbr_reds, &tmp, &nbr_filenames);
        printf("nbr of words: %zu\n", nbr_words);
        printf("nbr of reds: %zu\n", nbr_reds);
        printf("nbr of filenames: %zu\n", nbr_filenames);
        new_cmd = allocate_cmd(new_cmd, tmp2, nbr_words, nbr_reds, nbr_filenames);
        ft_lstadd_back(&table, new_node);
        if (tmp == NULL)
            break ;
        nbr_words = 0;
        nbr_reds = 0;
        nbr_filenames = 0;
        tmp = tmp->next;
        lines--;
        i++;
    }
    return (table);
}

t_list   *parser(t_list *token_list)
{
    t_list  *table;

    table = NULL;
    table = create_table(token_list, table);
    print_table(table);

    return (table);
}

// Heredoc works with cmd before it


// < hello | wc -l | grep a >> outfile >> out
// ls -la | cat -e | cat -e
// echo $PATH | tr : '\n'

// next steps
//  reduce the size of the function according to the norm
//  split functions into multiple files, store them in a way that makes sense
//  handle the freeing of everything upon error