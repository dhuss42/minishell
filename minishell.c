/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:04:16 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/27 13:13:03 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_loop(t_shell *shell)
{
	char	*input;

	while (1)
	{
		handle_signals(0);
		input = readline("minishell: ");
		handle_signals(1);
		if (!input)
		{
			printf("exit\n");
			return (clear_all(shell->env));
		}
		if (input[0] != '\0')
		{
			lexer(shell, input);
			parser(shell);
			// print_table(shell);
			expansion(shell, shell->env);
			// print_table(shell);
			executor(shell->env, shell->table, shell);
			add_history(input);
			free_minishell(shell, input);

			if (shell->exit == true)
				break ;
		}
	}
}

int	main(int argc, char *argv[], char **env)
{
	t_shell	shell;
	int		error_code;

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
	error_code = print_error(-1, NULL, NOTPRINT);
	return (error_code);
}
