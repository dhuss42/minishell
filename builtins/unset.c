/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:06:37 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/30 14:06:39 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

void get_len_unset(t_shell *shell, t_command *row)
{
    size_t j;
    size_t k;
    size_t counter;

    counter = 0;
    k = shell->i;
    while (row->args[k] != NULL)
    {
        j = 0;
        while (shell->env[j] != NULL)
        {
            if (ft_strncmp(row->args[k], shell->env[j], strlen_equal(shell->env[j])) == 0)
            {
                printf(GREEN"increasing counter\n"WHITE);
                counter++;
            }
            j++;
        }
        k++;
    }
    shell->len = j - counter;
}

int ft_unset(t_shell *shell, t_command *row)
{
    char    **tmp;
    size_t  j;
    size_t  k;
    size_t unset_index;
    bool    should_copy;

    get_len_unset(shell, row);
    // printf("shell->len: %zu\n", shell->len);
    tmp = malloc(sizeof(char *) * (shell->len + 1));
    if (!tmp)
    {
        print_error(errno, NULL, PRINT);
        return (-1);
    }
    j = 0;
    k = 0;
    // printf("TEST\n");
    while (shell->env[k] != NULL)
    {
        should_copy = true;
        unset_index = shell->i;
        while (row->args[unset_index] != NULL)
        {
            if (ft_strncmp(row->args[unset_index], shell->env[k], strlen_equal(shell->env[k])) == 0)
            {
                should_copy = false;
                break;
            }
            unset_index++;
        }
        if (should_copy == true)
        {
            tmp[j] = ft_strdup(shell->env[k]);
            if (!tmp[j])
            {
                clear_all(tmp);
                return (-1);
            }
            j++;
        }
        k++;
    }
    tmp[j] = NULL;

    if (shell->env)
        clear_all(shell->env);

    copy_env(tmp, shell);
    if (!shell->env)
        return (-1);

    clear_all(tmp);
    return (0);
}
