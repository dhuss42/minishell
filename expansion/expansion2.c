/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:41:27 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/18 16:17:05 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell_eichhoernchen.h"

size_t	strlen_equal_2(char *str)
{
	size_t  i;

	printf("TEST6\n");
	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	return (i);
}

char	*compare_with_env_2(char *variable, char **env, char *exp)
{

	size_t  j = 0;

	printf("TEST5\n");
		while (env[j] != NULL)
		{
			// printf("split_dollar: %s\n", split_dollar[i]);
			// printf("len: %zu\n", ft_strlen(split_dollar[i]));
			// printf("env: %s\n", env[j]);
			// printf("ft_len_equal: %zu\n", strlen_equal(env[j]));
			// printf("dif: %zu\n\n", ft_strlen(split_dollar[i]) - strlen_equal(env[j]));
			if (ft_strlen(variable) - strlen_equal_2(env[j]) == 0)
			{
				if (ft_strncmp(variable, env[j], strlen_equal_2(env[j])) == 0)
				{
					return (exp = ft_substr(env[j], strlen_equal_2(env[j]) + 1, ft_strlen(env[j]) - strlen_equal_2(env[j]) - 1));
				}
			}
			j++;
		}
	return (exp); // no idea here
}

size_t  get_len_exp_2(t_command *row, char *exp, size_t *i)
{
	size_t  j;
	size_t  len;

	printf("TEST7\n");
	j = 0;
	len = 0;
	printf("TEST7.1\n");
	printf(BLUE"get_len row-args: %s\n"WHITE, row->args[*i]);
	while(row->args[*i][j] != '\0' && !(row->args[*i][j] == '$' && ft_isalnum(row->args[*i][j + 1]))) // getting len up to first dollar
	{
		printf("TEST7.2\n");
		len++;
		j++;
	}
	while (row->args[*i][j] == '$')
		j++;
	printf(BLUE"len up to first dollar: %zu\n"WHITE, len);
	printf(BLUE"pos of row-args[*i][j]: %c\n", row->args[*i][j]);
	while(row->args[*i][j] != '\0' && row->args[*i][j] != '\"' && row->args[*i][j] != '$') // skipping until closing quote or dollar
		j++;
	printf(BLUE"pos of row-args[*i][j] after skip: %c\n", row->args[*i][j]);
	printf(BLUE"pos of row-args[*i][j + 1] after skip: %c\n", row->args[*i][j + 1]);
	while(row->args[*i][j] != '\0') // getting len of remainder
	{
		j++;
		len++;
	}
	printf(BLUE"len after closing quote: %zu\n"WHITE, len);
	printf(BLUE"pos of row-args[*i][j] final: %c\n", row->args[*i][j]);
	printf("TEST7.3\n");
	printf(RED"exp in get_len: %s\n"WHITE, exp);
	// printf("row->args[*i] %s\n", row->args[*i]);
	// printf("len: %zu\n", len);
	len += ft_strlen(exp);

	printf("TEST7.4\n");
	// printf("len: %zu\n", len);
	return (len);
}

// in ths function there could be issues for ordinary expansion and single quotes
// might have to adjust the get_len

void	switcheroo_2(t_command *row, char *exp, size_t *i, size_t *k)
{
	size_t  len;
	size_t  j;
	size_t  iterate;
	size_t  index;
	char	*tmp;

	j = 0;
	iterate = 0;
	index = 0;
	// printf("TEST6\n");
	len = get_len_exp_2(row, exp, i);
	// printf(BLUE"get len: %zu\n"WHITE, len);
	// printf("TEST1\n");
	// printf("TEST8\n");
	// tmp = malloc(sizeof(char) * (len + 1));
	tmp = ft_calloc(len + 1, sizeof(char));
	if (!tmp)
		return ;
	// printf("TEST2\n");
	// printf("TEST9\n");
	while(row->args[*i][j] != '\0' && !(row->args[*i][j] == '$' && ft_isalnum(row->args[*i][j + 1])))
		tmp[iterate++] = row->args[*i][j++];
	// printf(MAGENTA"tmp before exp: %s\n"WHITE, tmp);
	j++;
	// printf("TEST10\n");
	while(row->args[*i][j] != '\0' && row->args[*i][j] != '$' && row->args[*i][j] != '\"' && row->args[*i][j] != '\'')
		j++;
	// printf("before inserting expanded tmp: %s\n", tmp);
	// printf("row->args[i]: %s\n", row->args[*i]);
	// printf("row->args position[i]: %c\n", row->args[*i][j]);


	printf("TEST11\n");
	while (exp[index] != '\0')
		tmp[iterate++] = exp[index++];
	free(exp);
	// printf("after inserting expanded tmp: %s\n", tmp);
	// printf("strlen: %zu\n", ft_strlen(tmp));
	*k = iterate;
	// (*k)++;
	printf("k: %zu\n", *k);
	printf("TEST12\n");
	printf("row->args[*i][j] char: %c\n", row->args[*i][j]);
	while (row->args[*i][j] != '\0')
		tmp[iterate++] = row->args[*i][j++];

	tmp[iterate] = '\0';
	printf("tmp: %s\n", tmp);
	printf(BLUE"strlen tmp: %zu\n"WHITE, ft_strlen(tmp));
	printf(YELLOW" adress tmp: [%p]\n" WHITE, tmp);
	printf(YELLOW"adress row->args[*i]: [%p]\n"WHITE, row->args[*i]);
	// exit(EXIT_SUCCESS);

	// printf("before args[i]: %s\n", row->args[*i]);
	printf("TEST13\n");
	if (row->args[*i])
	{
		// printf(RED"Here is an issue\n"WHITE);
		free(row->args[*i]);
		row->args[*i] = NULL;
	}
	// printf("TESTHIER\n");
	size_t a = 0;
	while(row->args[a] != NULL)
	{
		printf("row->args[%zu]: %s\n", a, row->args[a]);
		a++;
	}
	printf("TEST14\n");
	printf("tmp: %s\n", tmp);
	printf("row->args[*i]: %s\n", row->args[*i]);
	printf("i: [%zu]\n", *i);
	row->args[*i] = ft_strdup(tmp);
	if (!row->args[*i])
		return ;
	printf(GREEN"after ft_strdup: row->args[%zu]: %s\n"WHITE, a, row->args[a]);
	printf("TEST15\n");
	if (tmp)
		free(tmp);
	printf("TEST16\n");
}

void	get_expanded_2(char *variable, char **env, t_command *row, size_t *i, size_t *k)
{
	// char	**split_dollar;
	char	*exp = NULL;
	// size_t  j = 0;

	printf("TEST4\n");
	while (*variable == '$')
		variable++;
	printf(MAGENTA"pos_dollar: %s\n"WHITE, variable);
	exp = compare_with_env_2(variable, env, exp);
	printf("exp: %s\n", exp);
	printf(YELLOW"address exp: %p\n"WHITE, exp);
	if (!exp)
	{
		exp = "";
		// row->args[*i][*k] = '\0';
		// ft_bzero(row->args[*i], ft_strlen(row->args[*i])); // should not be setting to zero because of $PATH$a$HOME
		// free(row->args[*i]);
		// row->args[*i][0] = '\0';
		// row->args[*i] = NULL;
		// return ;
	}

	switcheroo_2(row, exp, i, k); // reduce variables
}