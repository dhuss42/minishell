/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:28:36 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/19 12:10:10 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	replace_pwd(t_shell *shell, char *key, char *content)
{
	size_t	i;
	char	*new_pwd;
	bool	replaced;

	i = 0;
	replaced = false;
	while (shell->env[i] != NULL)
	{
		if (ft_strncmp(shell->env[i], key, strlen_equal(shell->env[i])) == 0)
		{
			new_pwd = ft_strjoin(key, content);
			if (!new_pwd)
				return (print_error(errno, NULL, PRINT));
			free(shell->env[i]);
			shell->env[i] = safe_ft_strdup(new_pwd);
			replaced = true;
			free(new_pwd);
			if (!shell->env[i])
				return (-1);
		}
		i++;
	}
	if (replaced == false)
		return (-1);
	return (0);
}

// the function needs proper handling for freeing things

char	**append_oldpwd(t_shell *shell, char *old_pwd, char **tmp)
{
	size_t	i;

	i = 0;
	while (shell->env[i] != NULL)
	{
		tmp[i] = ft_strdup(shell->env[i]);
		if (!tmp[i])
		{
			clear_all(tmp);
			return (NULL);
		}
		i++;
	}
	tmp[i] = ft_strdup(old_pwd);
	if (!tmp[i])
	{
		clear_all(tmp);
		return (NULL);
	}
	i++;
	tmp[i] = NULL;
	return (tmp);
}

int	allocate_oldpwd(t_shell *shell, char *old_pwd)
{
	size_t	i;
	char	**tmp;

	i = 0;
	while (shell->env[i] != NULL)
		i++;
	tmp = malloc(sizeof(char *) * (i + 2));
	if (!tmp)
		return (print_error(errno, NULL, PRINT));
	tmp = append_oldpwd(shell, old_pwd, tmp);
	if (!tmp)
		return (print_error(errno, NULL, PRINT));
	clear_all(shell->env);
	if (copy_env(tmp, shell) == -1)
		return (print_error(errno, NULL, PRINT));
	clear_all(tmp);
	return (0);
}

int	update_oldpwd(t_shell *shell, char *content)
{
	char		*new_pwd;

	new_pwd = NULL;
	if (replace_pwd(shell, "OLDPWD=", content) == -1)
	{
		new_pwd = ft_strjoin("OLDPWD=", content);
		if (!new_pwd)
		{
			free(content);
			return (print_error(errno, NULL, PRINT));
		}
		if (allocate_oldpwd(shell, new_pwd) != 0)
		{
			if (content)
				free(content);
			if (new_pwd)
				free(new_pwd);
			return (-1);
		}
	}
	if (content)
		free(content);
	if (new_pwd)
		free(new_pwd);
	return (0);
}

int	update_pwd(t_shell *shell)
{
	char	*pathname;

	pathname = getcwd(NULL, 0);
	if (!pathname)
		print_error(errno, NULL, PRINT);
	if (replace_pwd(shell, "PWD=", pathname) != 0)
	{
		if (pathname)
			free(pathname);
		return (-1);
	}
	if (pathname)
		free(pathname);
	return (0);
}
