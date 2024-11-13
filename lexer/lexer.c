
#include "../executor.h"

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
        return (free_three(NULL, trim_inpt, res));
    if (!trim_inpt)
        return (free_three(NULL, trim_inpt, res));
    res = safe_ft_strtrim(trim_inpt, " \n\t");
    if (!res)
        return (free_three(NULL, trim_inpt, res));
    tokens = split_space_quotes(res);
    if (!tokens)
        return (free_three(NULL, trim_inpt, res));
    shell->list = tokeniser(tokens);
    if (!shell->list)
        return (free_three(NULL, trim_inpt, res));
    shell->syntax_error = syntax_errors(shell->list);
    free_three(NULL, trim_inpt, res);
}

// echo "shit    i" hello |grep<file>>outfile|'"''whyallthe>quotes