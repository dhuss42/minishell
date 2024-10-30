/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:01:02 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/18 16:23:16 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_eichhoernchen.h"

void	parser(t_shell *shell)
{
	if (shell->syntax_error == true)
		return ;
	shell->table = NULL;
	if (create_table(shell) == -1)
	{
		// printf("I return after create table\n");
		return ;
	}
	if (!shell->table)
	{
		// printf("I return after check if table is empty\n");
		return ;
	}
	// printf(BLUE"TABLE IN PARSER\n"WHITE);
	// print_table(shell->table);

	// free_table(shell); // just here for leak check
}

// < hello | wc -l | grep a >> outfile >> out
// "$HOME" > out1 > out2 >> outmain | '     test' |        wc     -l | grep -lala > outfile
// ls -la | cat -e | cat -e
// echo $PATH | tr : '\n'
