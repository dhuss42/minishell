/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:41:21 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/21 16:29:22 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell_eichhoernchen.h"


t_list *expansion(t_list *table, char **env)
{
	if (iterate_table(table, env) == -1)
		return (NULL);
	if (remove_quotes(table) == -1)
		return (NULL);
	print_table(table);
	return (NULL);
}


