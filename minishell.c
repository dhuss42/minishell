
#include "minishell_eichhoernchen.h"

void    minishell_loop(t_list *list, t_list *table, char **env)
{
    while(1)
    {
        list = lexer(list);
        table = parser(list);
        print_table(table);
        expansion(table, env); // also need to pass env
        // ft_lstclear(&list, free_token);
    }
}


int	main(int argc, char *argv[], char **env)
{
    t_list	*list;
    t_list  *table;

    list = NULL;
    table = NULL;
    if (argc == 1)
        minishell_loop(list, table, env);
    (void) argv;
	return (0);
}

