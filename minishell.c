/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:04:16 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/14 11:42:57 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	minishell_loop(t_shell *shell)
{
	char	*input;

	while(1)
	{
		handle_signals(0);
		input = readline("minishell: ");
		handle_signals(1);
		if (!input)
			return clear_all(shell->env);
		if (input[0] != '\0')
		{
			lexer(shell, input);
			parser(shell);
			// print_table(shell);
			expansion(shell, shell->env);
			// print_table(shell);
			// test_builtins(shell);
			print_error(0, NULL, NOTPRINT);
			executor(shell->env, shell->table, shell);
			add_history(input);
			ft_lstclear(&shell->list, free_token);
			free_table(shell->table);
			free(input);
			// printf("Debug: Exit Code: %d\n", print_error(-1, NULL, NOTPRINT));
			if (shell->exit == true)
				break ;
		}
	}
}
	// problem with free_table and test_builtins
	// something is beeing freed which was not allocated

int	main(int argc, char *argv[], char **env)
{
	t_shell	shell;

	// printf("minishell started\n");
	init_terminal();
	shell.table = NULL;
	shell.exit = false;
	if (argc == 1)
	{
		if (copy_env(env, &shell) == -1)
			return (-1); //
		if (shlvl(&shell) != 0)
			return (-1);
		minishell_loop(&shell);
	}
	(void) argv;
	// printf("exiting minishell\n");
	return (print_error(-1, NULL, NOTPRINT));
}

// after executing a command we need to update _ variable in envs
