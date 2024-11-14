/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:04:16 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/14 10:41:03 by dhuss            ###   ########.fr       */
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
			print_error(0, NULL, NOTPRINT);
			// print_table(shell);
			// test_builtins(shell);
			executor(shell->env, shell->table, shell);
			add_history(input);
			ft_lstclear(&shell->list, free_token);
			free_table(shell->table);
			free(input);
		}
	}
}
	// problem with free_table and test_builtins
	// something is beeing freed which was not allocated

int	main(int argc, char *argv[], char **env)
{
	t_shell	shell;

	printf("minishell started\n");
	init_terminal();
	shell.table = NULL;
	if (argc == 1)
	{
		if (copy_env(env, &shell) == -1)
			return (-1); //
		if (shlvl(&shell) != 0)
			return (-1);
		minishell_loop(&shell);
	}
	(void) argv;
	return (0);
}

// after executing a command we need to update _ variable in envs
