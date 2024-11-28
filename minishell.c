/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:04:16 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/28 10:56:10 by maustel          ###   ########.fr       */
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
			return (clear_all(shell->env));
		if (input[0] != '\0')
		{
			lexer(shell, input);
			parser(shell);
			expansion(shell, shell->env);
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

	init_terminal();
	shell.table = NULL;
	shell.exit = false;
	if (argc == 1)
	{
		if (copy_env(env, &shell) == -1)
			return (-1);
		if (shlvl(&shell) != 0)
			return (-1);
		minishell_loop(&shell);
		printf("exit\n");
	}
	(void) argv;
	error_code = print_error(-1, NULL, NOTPRINT);
	return (error_code);
}
