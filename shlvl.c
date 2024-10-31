
#include "executor.h"

char    *update_shlvl(t_shell *shell, char *new_shlvl, size_t *i)
{
    int		shlvl;
    
    char	*pos;


	*i = 0;
	while (shell->env[*i] != NULL)
	{
		if (ft_strncmp(shell->env[*i], "SHLVL", strlen_equal(shell->env[*i])) == 0)
			break ;
		(*i)++;
	}
	pos = ft_strchr(shell->env[*i], '=');
	pos++;
	shlvl = ft_atoi(pos);
	shlvl++;
	new_shlvl = ft_itoa(shlvl);
	if (!new_shlvl)
    {
        print_error(errno, NULL, PRINT);
		return (NULL);
    }
	return (new_shlvl);
}

int	shlvl(t_shell *shell)
{
    size_t 	i;
    char	*new_shlvl;
	char 	*key;
	char	*res;

    new_shlvl = NULL;
    new_shlvl = update_shlvl(shell, new_shlvl, &i);
    if (!new_shlvl)
        return (print_error(errno, NULL, PRINT));
	key = malloc(sizeof(char) * (ft_strlen("SHLVL=") + 1));
	if (!key)
    {
        free(new_shlvl);
		return (print_error(errno, NULL, PRINT));
    }
	ft_strlcpy(key, "SHLVL=", ft_strlen("SHLVL=") + 1);
	res = ft_strjoin(key, new_shlvl);
	if (!res)
    {
        free_three(NULL, key, new_shlvl);
		return (print_error(errno, NULL, PRINT));
    }
	free(shell->env[i]);
	shell->env[i] = ft_strdup(res);
	if (!shell->env[i])
	{
		clear_all(shell->env);
		free_three(res, key, new_shlvl);
		return (print_error(errno, NULL, PRINT));
	}
    free_three(res, key, new_shlvl);
	return (0);
}
