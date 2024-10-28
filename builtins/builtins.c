
#include "../minishell_eichhoernchen.h"

void    test_builtins(t_shell *shell)
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
            if (ft_strncmp(row->args[shell->i], "echo", ft_strlen(row->args[shell->i])) == 0)
            {
                ft_echo(shell, row);
                    return ;
            }
            else if (ft_strncmp(row->args[shell->i], "pwd", ft_strlen(row->args[shell->i])) == 0)
            {
                if (ft_pwd() == -1)
                    return ;
            }
            else if (ft_strncmp(row->args[shell->i], "env", ft_strlen(row->args[shell->i])) == 0)
            {
                if (ft_env(shell) == -1)
                    return ;
            }
            else if (ft_strncmp(row->args[shell->i], "export", ft_strlen(row->args[shell->i])) == 0)
            {
                if (ft_export(shell, row) == -1)
                    return ;
            }
            else if (ft_strncmp(row->args[shell->i], "unset", ft_strlen(row->args[shell->i])) == 0)
            {
                if (ft_unset(shell, row) == -1)
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