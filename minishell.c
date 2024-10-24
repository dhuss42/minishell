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

void	minishell_loop(t_shell *shell, char **env)
{
	char	*input;

	while(1)
	{
    	input = readline("minishell: ");
    	if(!input)
       		return ;
		if (input[0] != '\0')
		{
			lexer(shell, input);
			parser(shell);
			print_table(shell->table);
			expansion(shell, env); // also need to pass env
			print_table(shell->table);

			ft_lstclear(&shell->list, free_token);
			free_table(shell);
		}
	}
}


int	main(int argc, char *argv[], char **env)
{
	t_shell	shell;

	shell.table = NULL;
	if (argc == 1)
		minishell_loop(&shell, env);
	(void) argv;
	return (0);
}
