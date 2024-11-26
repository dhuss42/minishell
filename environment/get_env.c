/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:30:04 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/24 14:02:35 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	copy_env(char **env, t_shell *shell)
{
	size_t	i;
	char	**new_env;

	i = 0;
	while (env[i] != NULL)
		i++;
	new_env = safe_malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (-1);
	i = 0;
	while (env[i] != NULL)
	{
		new_env[i] = safe_ft_strdup(env[i]);
		if (!new_env)
			return (clear_all(new_env), -1);
		i++;
	}
	new_env[i] = NULL;
	shell->env = duplicate_double_ptr(new_env);
	if (!shell->env)
		return (clear_all(new_env), -1);
	clear_all(new_env);
	return (0);
}
