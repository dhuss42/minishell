
#include "../minishell_eichhoernchen.h"

void  lexer(t_shell *shell, char *input)
{
	char	*trim_inpt;
	char	*res;
	char	**tokens;

    shell->list = NULL;
    tokens = NULL;
    res = NULL;
    shell->syntax_error = false;
    trim_inpt = trim_spaces(input, shell);
    if (shell->syntax_error == true)
        return (free_three(input, trim_inpt, res));
    if (!trim_inpt)
        return (free_three(input, trim_inpt, res));
    res = ft_strtrim(trim_inpt, " \n\t");
    if (!res)
    {
    //  print_error(errno, NULL);
        return (free_three(input, trim_inpt, res));
    }
    tokens = split_space_quotes(res);
    if (!tokens)
        return (free_three(input, trim_inpt, res));
    shell->list = tokeniser(tokens);
    if (!shell->list)
        return (free_three(input, trim_inpt, res));
    shell->syntax_error = syntax_errors(shell->list);
    free_three(input, trim_inpt, res);
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
// (x)there should be no space insertionbefore and after a dollar sign or $? or env
// (x)adjust get_len function so that is does not count extra spaces before and after $
// (x)probably need a new is_spacial function without $
// (x)handle correct splitting of Tokens
// ----- solved ----- //

// problem of unecessary Tokens
// --> reduce amount of Tokens
// --> code seems to works, it just contains unnecessary Tokens
// ----- solving ---- //
// (x)multiple Tokens should be treated as a Word Token
//      (x)in lexer
//      (x)in parser
// (x)have to check the legit filenames in parser because a filename cannot be an env
//      --> makes sense to do this somewhere else