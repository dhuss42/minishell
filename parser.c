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

/* t_command *handle_redirection(token *current_token, t_command *new_cmd)
{

    // allocation problem
    // I can get the amount of words or redirections in a block, but how do I avoid allocating everything over and over
    if (current_token->type == TOKEN_REDIN)

    else if (current_token == TOKEN_REDOUT)

    else if (current_token == TOKEN_REDAPPEND)

    else if (current_token == TOKEN_HEREDOC)

    return ();
} */

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

void    nbr_words_redirections(size_t *words, size_t *red, t_list **token_list)
{
    t_list  *tmp;
    token   *current_token;

    tmp = *token_list;
    *words = 0;
    *red = 0;
    while (tmp != NULL)
    {
        current_token = (token *)tmp->content;
        if (current_token->type == TOKEN_PIPE)
            break ;
        if (is_redirection(current_token))
        {
            // print_token(current_token);
            (*red)++;
        }
        // need to count file names too
        else
        {
            // print_token(current_token);
            (*words)++;
        }
        tmp = tmp->next;
    }
    *token_list = tmp;
}

t_command   *populate_cmd(t_command *new_cmd, t_list *tl_pos)
{
    token   *current_token;
    token   *next_token;
    t_list *tmp;
    size_t  i;

    i = 0;
    tmp = tl_pos;
    while(tmp != NULL)
    {
        current_token = (token *)tmp->content;
        if (current_token->type == TOKEN_PIPE)
            break ;
        // if (is_redirection(current_token) && is_filename(next_token = (token *)tmp->next->content)) // problem with iteration need to fix logic
        //     printf("TEST2\n");
        if (is_redirection(current_token))
        {
            printf("TEST\n");
            new_cmd->red_symbol[i] = malloc(sizeof(char) * (ft_strlen(current_token->input) + 1));
            if (!new_cmd->red_symbol[i])
                return (NULL); // free everything
            ft_strlcpy(new_cmd->red_symbol[i], current_token->input, ft_strlen(current_token->input) + 1);
            printf("REDIRECTION: [%s]\n", new_cmd->red_symbol[i]);
            if (is_filename(next_token = (token *)tmp->next->content))
                printf("TEST2\n");
            i++;
        }
        else 
        {
            printf("cmd and args\n");
        }
        tmp = tmp->next;
    }
    return (new_cmd);
}

t_command   *allocate_cmd(t_command *new_cmd, t_list *tl_pos, size_t wc, size_t rc)
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
        nbr_words_redirections(&nbr_words, &nbr_reds, &tmp);
        printf("nbr of words: %zu\n", nbr_words);
        printf("nbr of reds: %zu\n", nbr_reds);
        new_cmd = allocate_cmd(new_cmd, tmp2, nbr_words, nbr_reds);
        ft_lstadd_back(&table, new_node);
        if (tmp == NULL)
            break ;
        nbr_words = 0;
        nbr_reds = 0;
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

    return (table);
}

// < hello | wc -l | grep a >> outfile >> out