/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:04:16 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/30 15:56:13 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	minishell_loop(t_shell *shell)
{
	char	*input;

	while(1)
	{
    	input = readline("minishell: ");
    	// if(!input)
       	// 	return ;
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
			// ft_lstclear(&shell->list, free_token);

			free_table(shell->table);
		}
	}
}

int	copy_env(char **env, t_shell *shell)
{
	size_t i;
	char **new_env;

	i = 0;
	while (env[i] != NULL)
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
	{
		print_error(errno, NULL, PRINT);
		return (-1);
	}
	i = 0;
	while (env[i] != NULL)
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env)
		{
			print_error(errno, NULL, PRINT);
			clear_all(new_env);
			return (-1);
		}
		i++;
	}
	new_env[i] = NULL;
	shell->env = new_env;
	return (0);
}

int	main(int argc, char *argv[], char **env)
{
	t_shell	shell;

	printf("minisehll started\n");
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
