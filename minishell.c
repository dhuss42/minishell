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

void	minishell_loop(t_shell *shell)
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
			expansion(shell, shell->env); // also need to pass env
			print_table(shell->table);
			test_builtins(shell);

			ft_lstclear(&shell->list, free_token);
			free_table(shell);
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
	new_env = malloc (sizeof(char *) * (i + 1));
	if (!new_env)
		return (-1);
	i = 0;
	while (env[i] != NULL)
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env)
		{
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

	shell.table = NULL;
	if (argc == 1)
	{
		if (copy_env(env, &shell) == -1)
			return (-1); //
		minishell_loop(&shell);
	}
	(void) argv;
	return (0);
}
