/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:07:04 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/30 14:07:06 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_eichhoernchen.h"

bool    has_equal(const char *str)
{
    size_t i;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '=')
            return (true);
        i++;
    }
    return (false);
}

bool    valid_key_name(const char *str)
{
    size_t i;

    i = 0;
    if (!ft_isalpha(str[i]) && str[i] != '_')
        return (false);
    i++;
    while (str[i] != '\0' && str[i] != '=')
    {
        if (!(ft_isalnum(str[i]) || str[i] == '_'))
            return (false);
        i++;
    }
    return (true);
}

// checks if the key name is valid

int    key_exists(char **env, char *key)
{
    size_t  i;

    i = 0;
    while(env[i] != NULL)
    {
        if (ft_strncmp(key, env[i], strlen_equal(env[i])) == 0)
            return (i);
        i++;
    }
    return (-1);
}

// checks if the current key already exists in the og envs
// returns index when match is found
// returns -1 when they don't match

size_t  get_len_new_env(char **env, t_command *row, size_t i)
{
    size_t count;

    count = 0;
    while (env[count] != NULL)
        count++;
    // printf(YELLOW"count after env: %zu\n"WHITE, count);
    while (row->args[i] != NULL)
    {
        // printf(BLUE"current_var %s\n"WHITE, row->args[i]);
        if (has_equal(row->args[i]) && valid_key_name(row->args[i]) && (key_exists(env, row->args[i]) == -1))
        {
            // printf(GREEN"export count: %zu\n"WHITE, count);
            count++;
        }
        i++;
    }
    // printf(YELLOW"count total: %zu\n"WHITE, count);
    return (count);
}

// counts len of current env variables
// iterates through User input (args)
// if the structure is valid a counter is added
