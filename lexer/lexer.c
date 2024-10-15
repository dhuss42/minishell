
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

    printf("\033[32mTOKEN LINKED LIST\n");
    print_token_list(list);
    printf("\033[0m");
    syntax_errors(list);
    free(input);
    free(trim_inpt);
    free(res);
    // exit(EXIT_SUCCESS); // for debugging
    return (list);
}

// problem with echo hallo"welt"hallo
// --> bash: echo hallowelthallo
// --> solution: currently code is inserting ws before and after quotes
// --> also it is spliting according to quotes
// ---- solving ----- // 
// for proper quote handling remove ws insertion before and after the quotes (x)
// adjust get_len function so that it does not count extra spaces before and after quotes (x)
// adjust split_quotes function (x)
// ----- solved ------ //

// problem with separation of $
// --> currently separating like this $, $PATH, $?
// --> however might be more efficient to sort only like this $ 
// --> makes it easier in expansion, searches only in the next array of args for the next chars ft_isalnum or specifically ?
// ---- solving ------ //
// ()there should be no space insertionbefore and after a dollar sign or $? or env
// ()should be treated as a Word Token
// ()have to check the legit filenames in parser because a filename cannot be an env
// ()adjust get_len function so that is does not count extra spaces before and after $
// ()probably need a new is_spacial function without $


// problem with echo$PATH
// --> get_len does not count $ as a character for inserting ws before

// problem of unecessary Tokens
// --> reduce amount of Tokens