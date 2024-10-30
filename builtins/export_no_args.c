/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:06:57 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/30 14:06:58 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "../minishell_eichhoernchen.h"

char    **allocate_sorted(t_shell *shell, char **sorted)
{
    shell->k = 0;
        while(shell->env[shell->k] != NULL)
            shell->k++;
        sorted = malloc(sizeof(char *) * (shell->k + 1));
        if (!sorted)
        {
            //print error
            return (NULL);
        }
        shell->k = 0;
        while(shell->env[shell->k] != NULL)
        {
            sorted[shell->k] = ft_strdup(shell->env[shell->k]);
            if (!sorted[shell->k])
            {
                //print error
                clear_all(sorted);
                return (NULL);
            }
            shell->k++;
        }
    return (sorted);
}

char    **bubble_sort(t_shell *shell)
{
    size_t i;
    char    *tmp;
    char    **sorted;

    sorted = NULL;
    sorted = allocate_sorted(shell, sorted);
    if (!sorted)
        return (NULL);
    i = 0;
    while (i < shell->k - 1)
    {
        shell->j = 0;
        while (shell->j < shell->k - i - 1)
        {
            if (strlen_equal(sorted[shell->j]) > strlen_equal(sorted[shell->j + 1]))
                shell->len = strlen_equal(sorted[shell->j]);
            else
                shell->len = strlen_equal(sorted[shell->j + 1]);
            if (ft_strncmp(sorted[shell->j], sorted[shell->j + 1], shell->len) > 0)
            {
                tmp = sorted[shell->j];
                sorted[shell->j] = sorted[shell->j + 1];
                sorted[shell->j + 1] = tmp;
            }
            shell->j++;
        }
        i++;
    }
    return (sorted);
}

void    put_str_n(char *str, size_t n, size_t i)
{
    while (str[i] != '\0' && i < n)
        write(1, &str[i++], 1);
}

void    export_no_argument(t_shell *shell)
{
    size_t  i;
    char    **sorted;

    i = 0;
    sorted = bubble_sort(shell);
    if (!sorted)
        return ;
    while (sorted[i] != NULL)
    {
        if (ft_strncmp(sorted[i], "_=./minishell", ft_strlen(sorted[i])) != 0) // need to find out when to skip and when not
        {
            ft_printf("declare -x ");
            put_str_n(sorted[i], strlen_equal(sorted[i]) + 1, 0);
            write(1, "\"", 1);
            put_str_n(sorted[i], ft_strlen(sorted[i]), strlen_equal(sorted[i]) + 1);
            write(1, "\"\n", 2);
        }
        i++;
    }
    clear_all(sorted);
}
