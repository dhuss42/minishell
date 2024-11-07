#include "../executor.h"

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