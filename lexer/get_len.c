
#include "../minishell_eichhoernchen.h"

/*---for-debugging------/ 
size_t	get_len(char *str)
{
	t_shell	nbr;
	char	quotes = '\0';

	nbr.i = 0;
	nbr.len = 0;
	while (str[nbr.i] != '\0')
	{
		if (is_wspace(str[nbr.i]))
		{
			// printf("\e[0;34mis a whitespace: \n\e[0;37m");
			nbr.len++;
			// printf("len: %zu\n", nbr.len);
			while (is_wspace(str[nbr.i]) && str[nbr.i] != '\0')
			{
				// printf("skipping whitespaces: \n");
				nbr.i++;
			}
		}
		else if (str[nbr.i] == '\'' || str[nbr.i] == '\"')
		{
			if (nbr.i != 0 && !is_wspace(str[nbr.i - 1]) && !is_special(str[nbr.i - 1])) // adding is_special here
			{
				nbr.len++;
				// printf("adding whitespace\n");
				// printf("len: %zu\n", nbr.len);
			}
			// printf("\e[0;31mis a quote: \e[0;37m\n");
			quotes = str[nbr.i];
			nbr.i++;
			nbr.len++;
			// printf("len: %zu\n", nbr.len);
			while (str[nbr.i] != quotes && str[nbr.i] != '\0')
			{
				nbr.i++;
				nbr.len++;
				// printf("len: %zu\n", nbr.len);
				if (str[nbr.i] == '\0')
					printf("ERROR NO CLOSING QUOTES\n");
			}
			// printf("\e[0;31mis a closing quote: \e[0;37m\n");
			if (str[nbr.i] == quotes)
			{
				nbr.i++;
				nbr.len++;
			}
			// printf("len: %zu\n", nbr.len);
			if (str[nbr.i] != '\0' && !is_wspace(str[nbr.i]))
			{
				nbr.len++;
				// printf("adding whitespace\n");
				// printf("len: %zu\n", nbr.len);
			}
		}

		else if ((str[nbr.i] == '<' && str[nbr.i + 1] == '<') || (str[nbr.i] == '>' && str[nbr.i + 1] == '>'))
		{
			if (nbr.i != 0 && !is_wspace(str[nbr.i - 1]) && !is_special(str[nbr.i - 1])) // adding is_special here
			{
				nbr.len++;
				// printf("adding whitespace\n");
				// printf("len: %zu\n", nbr.len);
			}
			// printf("\e[0;33mis << or >>: \e[0;37m\n");
			nbr.len += 2;
			// printf("len: %zu\n", nbr.len);

			if (str[nbr.i + 2] != '\0' && !is_wspace(str[nbr.i + 2]))
			{
				nbr.len++;
				// printf("adding whitespace\n");
				// printf("len: %zu\n", nbr.len);
			}
			nbr.i += 2;
		}
		else if (is_special(str[nbr.i]) && !(str[nbr.i] == '$' && (str[nbr.i + 1] == '?' || ft_isalnum(str[nbr.i + 1]))))
		{
			if (nbr.i != 0 && !is_wspace(str[nbr.i - 1]) && !is_special(str[nbr.i - 1])) // adding !is_special here
			{
				nbr.len++;
				// printf("adding whitespace\n");
				// printf("len: %zu\n", nbr.len);
			}
			// printf("\e[0;33mis a special char: \e[0;37m\n");
			nbr.len ++;
			// printf("len: %zu\n", nbr.len);

			if (str[nbr.i + 1] != '\0' && !is_wspace(str[nbr.i + 1]))
			{
				nbr.len++;
				// printf("adding whitespace\n");
				// printf("len: %zu\n", nbr.len);
			}
			nbr.i ++;
		}
		else
		{
			// printf("\e[0;35mis an oridnary char: \e[0;37m\n");
			nbr.len++;
			nbr.i++;
			// printf("len: %zu\n", nbr.len);
		}
	}
	return (nbr.len); 
}
*/

void    get_len_ws(t_shell *nbr, char *str)
{
    nbr->len++;
	while (is_wspace(str[nbr->i]) && str[nbr->i] != '\0')
		nbr->i++;
}

void    get_len_quotes(t_shell *nbr, char *str)
{
    char	quotes = '\0';

    if (nbr->i != 0 && !is_wspace(str[nbr->i - 1]) && !is_special(str[nbr->i - 1]))
				nbr->len++;
	quotes = str[nbr->i];
	nbr->i++;
	nbr->len++;
	while (str[nbr->i] != quotes && str[nbr->i] != '\0')
	{
		nbr->i++;
		nbr->len++;
	}
	if (str[nbr->i] == '\0')
    {
		printf("ERROR NO CLOSING QUOTES\n");
        exit(EXIT_FAILURE);
    }
	if (str[nbr->i] == quotes)
	{
		nbr->i++;
		nbr->len++;
	}
	if (str[nbr->i] != '\0' && !is_wspace(str[nbr->i]))
		nbr->len++;
}

void    get_len_special(t_shell *nbr, char *str)
{
    if (nbr->i != 0 && !is_wspace(str[nbr->i - 1]) && !is_special(str[nbr->i - 1]))
		nbr->len++;
	nbr->len ++;
	if (str[nbr->i + 1] != '\0' && !is_wspace(str[nbr->i + 1]))
		nbr->len++;
	nbr->i ++;
}

void    get_len_double_red(t_shell *nbr, char *str)
{
	if (nbr->i != 0 && !is_wspace(str[nbr->i - 1]) && !is_special(str[nbr->i - 1]))
		nbr->len++;
	nbr->len += 2;
	if (str[nbr->i + 2] != '\0' && !is_wspace(str[nbr->i + 2]))
		nbr->len++;
	nbr->i += 2;
}

size_t	get_len(char *str)
{
	t_shell	nbr;

	nbr.i = 0;
	nbr.len = 0;
	while (str[nbr.i] != '\0')
	{
		if (is_wspace(str[nbr.i]))
            get_len_ws(&nbr, str);
		else if (str[nbr.i] == '\'' || str[nbr.i] == '\"')
			get_len_quotes(&nbr, str);
		else if ((str[nbr.i] == '<' && str[nbr.i + 1] == '<') || (str[nbr.i] == '>' && str[nbr.i + 1] == '>'))
            get_len_double_red(&nbr, str);
		else if (is_special(str[nbr.i]) && !(str[nbr.i] == '$' && (str[nbr.i + 1] == '?' || ft_isalnum(str[nbr.i + 1]))))
            get_len_special(&nbr, str);
		else
		{
			nbr.len++;
			nbr.i++;
		}
	}
	return (nbr.len);
}
