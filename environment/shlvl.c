/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:19:30 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/27 15:00:19 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	find_index(t_shell *shell, int *i)
{
	*i = 0;
	while (shell->env[*i] != NULL)
	{
		if (ft_strncmp(shell->env[*i], "SHLVL",
				strlen_equal(shell->env[*i])) == 0)
			break ;
		(*i)++;
	}
	if (shell->env[*i] == NULL)
		(*i) = -2;
}

char	*update_shlvl(t_shell *shell, char *new_shlvl, int *i)
{
	int		shlvl;
	char	*pos;

	find_index(shell, i);
	pos = ft_strchr(shell->env[*i], '=');
	pos++;
	shlvl = ft_atoi(pos);
	shlvl++;
	new_shlvl = ft_itoa(shlvl);
	if (!new_shlvl)
	{
		print_error(errno, NULL, PRINT);
		return (NULL);
	}
	return (new_shlvl);
}

int	shlvl(t_shell *shell)
{
	int		i;
	char	*new_shlvl;
	char	*key;
	char	*res;

	if (shell->env[0] == NULL)
		return (0);
	new_shlvl = NULL;
	new_shlvl = update_shlvl(shell, new_shlvl, &i);
	if (!new_shlvl && i != -2)
		return (-1);
	key = safe_malloc(sizeof(char) * (ft_strlen("SHLVL=") + 1));
	if (!key)
		return (free(new_shlvl), -1);
	ft_strlcpy(key, "SHLVL=", ft_strlen("SHLVL=") + 1);
	res = ft_strjoin(key, new_shlvl);
	if (!res)
		return (free_three(NULL, key, new_shlvl), -1);
	free(shell->env[i]);
	shell->env[i] = safe_ft_strdup(res);
	if (!shell->env[i])
		return (clear_all(shell->env), free_three(res, key, new_shlvl), -1);
	free_three(res, key, new_shlvl);
	return (0);
}
