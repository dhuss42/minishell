/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:04:16 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/18 16:04:51 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_eichhoernchen.h"

void	minishell_loop(t_list *list, t_list *table, char **env)
{
	char	*input;

	while(1)
	{
    	input = readline("minishell: ");
    	if(!input)
       		return ;
		if (input[0] != '\0')
		{
			list = lexer(list, input);
			table = parser(list);
			print_table(table);
			expansion(table, env); // also need to pass env
			// ft_lstclear(&list, free_token);
			
		}
		// exit(EXIT_SUCCESS);
	}
}


int	main(int argc, char *argv[], char **env)
{
	t_list	*list;
	t_list  *table;

	list = NULL;
	table = NULL;
	if (argc == 1)
		minishell_loop(list, table, env);
	(void) argv;
	return (0);
}

