
#include "../minishell_eichhoernchen.h"

void	test_builtins(t_shell *shell)
{
	t_command   *row;

	if (shell->syntax_error == true)
		return ;
	while (shell->table != NULL)
	{
		row = (t_command*) shell->table->content;
		shell->i = 0;
		while (row->args[shell->i] != NULL)
		{
			if (ft_strncmp(row->args[shell->i], "echo", /* ft_strlen(row->args[shell->i])) */4) == 0 /* && ft_strlen(row->args[shell->i]) == 4 */)
			{
				ft_echo(shell, row);
					return ;
			}
			else if (ft_strncmp(row->args[shell->i], "pwd", ft_strlen(row->args[shell->i])) == 0 && ft_strlen(row->args[shell->i]) == 3)
			{
				if (ft_pwd() == -1)
					return ;
			}
			else if (ft_strncmp(row->args[shell->i], "env", ft_strlen(row->args[shell->i])) == 0 && ft_strlen(row->args[shell->i]) == 3)
			{
				if (ft_env(shell) == -1)
					return ;
			}
			else if (ft_strncmp(row->args[shell->i], "export", ft_strlen(row->args[shell->i])) == 0 && ft_strlen(row->args[shell->i]) == 6)
			{
				if (ft_export(shell, row) == -1)
					return ;
			}
			else if (ft_strncmp(row->args[shell->i], "unset", ft_strlen(row->args[shell->i])) == 0 && ft_strlen(row->args[shell->i]) == 5)
			{
				if (ft_unset(shell, row) == -1)
					return ;
			}
			else if (ft_strncmp(row->args[shell->i], "cd", ft_strlen(row->args[shell->i])) == 0 && ft_strlen(row->args[shell->i]) == 2)
			{
				if (ft_cd(shell, row) == -1)
					return ;
			}
			else if (ft_strncmp(row->args[shell->i], "exit", ft_strlen(row->args[shell->i])) == 0 && ft_strlen(row->args[shell->i]) == 4)
			{
				ft_exit(row);
					return ;
			}
			// if (row->args[shell->i] == NULL)
				break ;
			shell->i++;
		}
		shell->table = shell->table->next;
	}
}

// not sure if the while loop is necessary
// handle this case
// --> export t="cho hallo"
// --> e$t
// -----> should be [echo] [hallo]
// -----> currently is [echo hallo]