/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:07:20 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/30 14:07:31 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_eichhoernchen.h"

int    ft_env(t_shell *shell)
{
    size_t i;

    if (shell->env == NULL)
        return (-1);
    i = 0;
    while (shell->env[i] != NULL)
        ft_printf("%s\n", shell->env[i++]);
    return (0);
}

/* int main(int argc, char *argv[], char **env)
{
    (void) argc;
    (void) argv;
    ft_env(env);
    return (0);
} */
