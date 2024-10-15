/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:01:02 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/10 11:26:24 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_eichhoernchen.h"

t_list	*parser(t_list *token_list)
{
	t_shell	parsing;

	parsing.table = NULL;
	parsing.table = create_table(token_list, &parsing);
	// print_table(parsing.table);

	// free_table(&parsing); // just here for leak check
	return (parsing.table);
}

// < hello | wc -l | grep a >> outfile >> out
// "$HOME" > out1 > out2 >> outmain | '     test' |        wc     -l | grep -lala > outfile
// ls -la | cat -e | cat -e
// echo $PATH | tr : '\n'
