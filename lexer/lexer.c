
#include "../minishell_eichhoernchen.h"

t_list  *lexer(t_list *list)
{
	char	*trim_inpt;
	char	*res;
	char	**tokens = NULL;
    char	*input;

    input = readline("minishell: ");
    if(!input)
        return (NULL);

    trim_inpt = trim_spaces(input);
    res = ft_strtrim(trim_inpt, " \n\t");

    tokens = split_space_quotes(res);

    list = tokeniser(tokens);

    // printf("\033[32mTOKEN LINKED LIST\n");
    // print_token_list(list);
    // printf("\033[0m");
    syntax_errors(list);
    free(input);
    free(trim_inpt);
    free(res);
    return (list);
}

// problem with echo hallo"welt"hallo
// --> bash: echo hallowelthallo
// --> solution: currently code is inserting ws before and after quotes
// --> also it is spliting according to quotes

// problem with separation of $
// --> currently separating like this $, $PATH, $?
// --> however might be more efficient to sort only like this $ 
// --> makes it easier in expansion, searches only in the next array of args for the next chars ft_isalnum or specifically ?

// problem of unecessary Tokens
// --> reduce amount of Tokens