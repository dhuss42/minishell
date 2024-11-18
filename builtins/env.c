/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:07:20 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/18 14:12:31 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_eichhoernchen.h"

int	ft_env(t_shell *shell)
{
	size_t	i;

	if (shell->env == NULL)
		return (-1); // not sure what is suppossed to happen
	i = 0;
	while (shell->env[i] != NULL)
	{
		if (has_equal(shell->env[i]))
			ft_printf("%s\n", shell->env[i]);
		i++;
	}
	return (0);
}
