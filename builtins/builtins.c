
#include "../executor.h"

int	builtins(t_shell *shell, t_command *row)
{
	// t_command   *row;

	if (shell->table == NULL)
		return (-1);
	// row = (t_command*) shell->table->content;
	shell->i = 0;
	if (row->args[0] == NULL)
		return (1);
	if (ft_strlen(row->args[0]) == 2)
	{
		if (ft_strncmp(row->args[0], "cd", 2) == 0)
			return (ft_cd(shell, row));
	}
	else if (ft_strlen(row->args[0]) == 3)
	{
		if (ft_strncmp(row->args[0], "pwd", 3) == 0)
			return (ft_pwd());
		else if (ft_strncmp(row->args[0], "env", 3) == 0)
			return (ft_env(shell));
	}
	else if (ft_strlen(row->args[0]) == 4)
	{
		if (ft_strncmp(row->args[0], "echo", 4) == 0)
			return (ft_echo(shell, row));
		else if (ft_strncmp(row->args[0], "exit", 4) == 0)
			return (ft_exit(shell,row));
	}
	else if (ft_strlen(row->args[0]) == 5)
	{
		if (ft_strncmp(row->args[0], "unset", 5) == 0)
		return (ft_unset(shell, row));
	}
	else if (ft_strlen(row->args[0]) == 6)
	{
		if (ft_strncmp(row->args[0], "export", 6) == 0)
			return (ft_export(shell, row));
	}
	return (1);
}

int	check_builtins(t_shell *shell, t_command *row)
{
	if (builtins(shell, row) == 0)
	{
		// printf("---------------IS BUILTIN---------------\n");
		// usleep(30000);
		dup2(row->original_stdout, STDOUT_FILENO);
		dup2(row->original_stdin, STDIN_FILENO);
		return (0);
	}
	else if (builtins(shell, row) < 0)
	{
		dup2(row->original_stdout, STDOUT_FILENO);
		dup2(row->original_stdin, STDIN_FILENO);
		return (print_error(E_BUILTIN, NULL, PRINT));
	}
	return (1);
}
