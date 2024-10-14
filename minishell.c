
#include "minishell_eichhoernchen.h"

void    minishell_loop(t_list *list)
{
    while(1)
    {
        list = lexer(list);
        parser(list); // returns table
        ft_lstclear(&list, free_token);
    }
}


int	main()
{
    t_list	*list;

    list = NULL;
    minishell_loop(list);
	return (0);
}

