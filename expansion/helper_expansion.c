

#include "../minishell_eichhoernchen.h"

bool	is_quotes(char c)
{
	if (c == '\'')
		return (true);
	if (c == '\"')
		return (true);
	return (false);
}

bool	contains_dollar(char *str, size_t i)
{
	if (str[i] == '\"')
		i++;
	while (str[i] != '\0' && str[i] != '\"')
	{
		if (str[i] == '$')
			return (true);
		i++;
	}
	return (false);
}
