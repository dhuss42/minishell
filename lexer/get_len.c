
#include "../executor.h"

// ---for-debugging------/
// size_t	get_len(char *str)
// {
// 	t_shell	nbr;
// 	char	quotes = '\0';

// 	nbr.i = 0;
// 	nbr.len = 0;
// 	while (str[nbr.i] != '\0')
// 	{
// 		if (is_wspace(str[nbr.i]))
// 		{
// 			printf("\e[0;34mis a whitespace: \n\e[0;37m");
// 			nbr.len++;
// 			printf("len: %zu\n", nbr.len);
// 			while (is_wspace(str[nbr.i]) && str[nbr.i] != '\0')
// 			{
// 				printf("skipping whitespaces: \n");
// 				nbr.i++;
// 			}
// 		}
// 		else if (str[nbr.i] == '\'' || str[nbr.i] == '\"')
// 		{
// 			printf("\e[0;31mis a quote: \e[0;37m\n");
// 			quotes = str[nbr.i];
// 			nbr.i++;
// 			nbr.len++;
// 			printf("len: %zu\n", nbr.len);
// 			while (str[nbr.i] != quotes && str[nbr.i] != '\0')
// 			{
// 				nbr.i++;
// 				nbr.len++;
// 				printf("len: %zu\n", nbr.len);
// 				if (str[nbr.i] == '\0')
// 					printf("ERROR NO CLOSING QUOTES\n");
// 			}
// 			printf("\e[0;31mis a closing quote: \e[0;37m\n");
// 			if (str[nbr.i] == quotes)
// 			{
// 				nbr.i++;
// 				nbr.len++;
// 			}
// 			printf("len: %zu\n", nbr.len);
// 		}
// 		else if ((str[nbr.i] == '<' && str[nbr.i + 1] == '<') || (str[nbr.i] == '>' && str[nbr.i + 1] == '>'))
// 		{
// 			if (nbr.i != 0 && !is_wspace(str[nbr.i - 1]) && !is_special_no_quotes(str[nbr.i - 1]))
// 			{
// 				nbr.len++;
// 				printf("adding whitespace\n");
// 				printf("len: %zu\n", nbr.len);
// 			}
// 			printf("\e[0;33mis << or >>: \e[0;37m\n");
// 			nbr.len += 2;
// 			printf("len: %zu\n", nbr.len);

// 			if (str[nbr.i + 2] != '\0' && !is_wspace(str[nbr.i + 2]))
// 			{
// 				nbr.len++;
// 				printf("adding whitespace\n");
// 				printf("len: %zu\n", nbr.len);
// 			}
// 			nbr.i += 2;
// 		}
// 		else if (is_special_no_quotes(str[nbr.i]) /*&& !(str[nbr.i] == '$' && (str[nbr.i + 1] == '?' || ft_isalnum(str[nbr.i + 1]))) */)
// 		{
// 			if (nbr.i != 0 && !is_wspace(str[nbr.i - 1]) && !is_special_no_quotes(str[nbr.i - 1]))
// 			{
// 				nbr.len++;
// 				printf("adding whitespace\n");
// 				printf("len: %zu\n", nbr.len);
// 			}
// 			printf("\e[0;33mis a special char: \e[0;37m\n");
// 			nbr.len ++;
// 			printf("len: %zu\n", nbr.len);

// 			if (str[nbr.i + 1] != '\0' && !is_wspace(str[nbr.i + 1]))
// 			{
// 				nbr.len++;
// 				printf("adding whitespace\n");
// 				printf("len: %zu\n", nbr.len);
// 			}
// 			nbr.i ++;
// 		}
// 		else
// 		{
// 			printf("\e[0;35mis an oridnary char: \e[0;37m\n");
// 			nbr.len++;
// 			nbr.i++;
// 			printf("len: %zu\n", nbr.len);
// 		}
// 	}
// 	return (nbr.len);
// }


// --top-- for debugging ------- //
// --bottom-- correct function --//

void	get_len_ws(t_shell *nbr, char *str)
{
	nbr->len++;
	while (is_wspace(str[nbr->i]) && str[nbr->i] != '\0')
		nbr->i++;
}

void    get_len_quotes(t_shell *nbr, char *str, t_shell *shell)
{
    char	quotes[2];

	quotes[0] = str[nbr->i];
	quotes[1] = '\0';
	nbr->i++;
	nbr->len++;
	while (str[nbr->i] != quotes[0] && str[nbr->i] != '\0')
	{
		nbr->i++;
		nbr->len++;
	}
	if (str[nbr->i] == '\0')
    {
		shell->syntax_error = true;
		print_error(E_SYNTAXERROR, quotes, PRINT);
		return ;
    }
	if (str[nbr->i] == quotes[0])
	{
		nbr->i++;
		nbr->len++;
	}
}

void    get_len_special(t_shell *nbr, char *str)
{
    if (nbr->i != 0 && !is_wspace(str[nbr->i - 1]) && !is_special_no_quotes(str[nbr->i - 1]))
		nbr->len++;
	nbr->len ++;
	if (str[nbr->i + 1] != '\0' && !is_wspace(str[nbr->i + 1]))
		nbr->len++;
	nbr->i ++;
}

void    get_len_double_red(t_shell *nbr, char *str)
{
	if (nbr->i != 0 && !is_wspace(str[nbr->i - 1]) && !is_special_no_quotes(str[nbr->i - 1]))
		nbr->len++;
	nbr->len += 2;
	if (str[nbr->i + 2] != '\0' && !is_wspace(str[nbr->i + 2]))
		nbr->len++;
	nbr->i += 2;
}

size_t	get_len(char *str, t_shell *shell)
{
	t_shell	nbr;

	nbr.i = 0;
	nbr.len = 0;
	while (str[nbr.i] != '\0')
	{
		if (is_wspace(str[nbr.i]))
            get_len_ws(&nbr, str);
		else if (str[nbr.i] == '\'' || str[nbr.i] == '\"')
			get_len_quotes(&nbr, str, shell);
		else if ((str[nbr.i] == '<' && str[nbr.i + 1] == '<') || (str[nbr.i] == '>' && str[nbr.i + 1] == '>'))
            get_len_double_red(&nbr, str);
		else if (is_special_no_quotes(str[nbr.i]))
            get_len_special(&nbr, str);
		else
		{
			nbr.len++;
			nbr.i++;
		}
	}
	return (nbr.len);
}


// ls -la|echo$PATH
// echo hallo"welt     "hallo
// echo $PATHhome$HOME" .   hallo $?"     >>'$$?'<<infile>out|$
// --> not adding ws before quote in get_len
// 			--> removing quotes from is_special_no_quotes solved it
// 			--> however it affects something else so the spaces inside the quotes are trimmed
// 			-------solved-------
// --> not splitting correct after quote also
// 			------solved-------

// "$?      "<'""'|   "out"        <<in

// "asd" "'    fgd  "t t | sa $TEST $sa
// --> not splitting correct
// 			------solved-------
// --> setting isspace flag to false solved it

// halla < >ads>
// --> funktioniert wirft syntax error wegen < >
// test "asd"asd"asds"
// --> funktioniert
// "asd" "'    fgd  "t t | sa $TEST $sa echo hallo"welt    "hallo""