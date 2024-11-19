/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_with_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:38:59 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/19 12:08:59 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	strlen_equal(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	return (i);
}

char	*compare_with_env(char *variable, char **env, char *exp)
{
	size_t	j;

	j = 0;
	while (env[j] != NULL)
	{
		if (ft_strlen(variable) - strlen_equal(env[j]) == 0)
		{
			if (ft_strncmp(variable, env[j], strlen_equal(env[j])) == 0)
			{
				return (exp = safe_ft_substr(env[j], strlen_equal(env[j])
						+ 1, ft_strlen(env[j]) - strlen_equal(env[j]) - 1));
			}
		}
		j++;
	}
	if (!exp)
		return (exp = safe_ft_strdup(""));
	return (NULL);
}

// compares the variable name (PATH) to every string in the env** list
// env strings are only compared up until the equal sign =
// returns when the variable and the env are equal up until the '=' sign
