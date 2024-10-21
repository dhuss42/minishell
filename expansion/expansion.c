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


t_list *expansion(t_list *table, char **env) // change to our env
{
	iterate_table(table, env); // cif there are no quotes go into check_for_dollar
	remove_quotes(table);
	print_table(table);
	return (NULL);
}


// '$PATH'''$HOME''
// --> '$PATH' is being replaced by $HOME