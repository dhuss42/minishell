/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:07:34 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/05 15:52:50 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

char *search_env(char **env, char *key)
{
	size_t	i;
	char	*str;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], key, strlen_equal(env[i])) == 0)
		{
			str = ft_substr(env[i], strlen_equal(env[i]) + 1, ft_strlen(env[i]) - strlen_equal(env[i]) - 1);
			return (str);
		}
		i++;
	}
	return (NULL);
}

// get HOME key
// compare with env and get string following the = sign
// use the string as the arg for cddir
// check for error if HOME does not exist or is not set

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
			shell->env[i] = ft_strdup(new_pwd);
			replaced = true;
			free(new_pwd);
			if (!shell->env[i])
				return (print_error(errno, NULL, PRINT));
		}
		i++;
	}
	if (replaced == false)
		return (-1);
	return (0);
}

int	append_oldpwd(t_shell *shell, char *old_pwd)
{
	size_t	i;
	char	**tmp;

	i = 0;
	while (shell->env[i] != NULL)
		i++;
	tmp = malloc(sizeof(char *) * (i + 2));
	if (!tmp)
		return (print_error(errno, NULL, PRINT));
	i = 0;
	while (shell->env[i] != NULL)
	{
		tmp[i] = ft_strdup(shell->env[i]);
		if (!tmp[i])
		{
			clear_all(tmp);
			return (print_error(errno, NULL, PRINT));
		}
		i++;
	}
	tmp[i] = ft_strdup(old_pwd);
	if (!tmp[i])
	{
		clear_all(tmp);
		return (print_error(errno, NULL, PRINT));
	}
	i++;
	tmp[i] = NULL;
	clear_all(shell->env);
	if (copy_env(tmp, shell) == -1)
		return (print_error(errno, NULL, PRINT));
	clear_all(tmp);
	return (0);
}

int	update_oldpwd(t_shell *shell, char *content)
{
	// char		*content;
	char		*new_pwd;

	new_pwd = NULL;
	// I think I should get the string following pwd before I call chdir but update oldpwd after I call chdir
	// content = search_env(shell->env, "PWD");
	// if (!content)
	// 	return (print_error(errno, "PWD", PRINT));
	if (replace_pwd(shell, "OLDPWD=", content) == -1)
	{
		new_pwd = ft_strjoin("OLDPWD=", content);
		if (!new_pwd)
		{
			free(content);
			return (print_error(errno, NULL, PRINT));
		}
		if (append_oldpwd(shell, new_pwd) != 0)
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
	char *pathname;

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


int	cd_no_args(t_shell *shell, t_command *row, char *current_dir)
{
	char *no_args;

	no_args = search_env(shell->env, "HOME");
	if (!no_args)
		return (print_error(E_NOTSET, "HOME", PRINT));
	// I think here should be the part where for HOME=
	// in this case cd does nothing but changes the oldpwd
	if (chdir(no_args) == -1)
		return (print_error(errno, row->args[1], PRINT));
	if (update_oldpwd(shell, current_dir) != 0)
		return (-1);
	if (update_pwd(shell) != 0)
		return (-1);
	if(no_args)
		free(no_args);
	return (0);
}

int		ft_cd(t_shell *shell, t_command *row)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		return (print_error(errno, NULL, PRINT));

	if (!row->args[1])
	{
		if (cd_no_args(shell, row, current_dir) != 0)
			return (-1);
	}
	else if (row->args[1])
	{
		if (chdir(row->args[1]) == -1)
			return (print_error(errno, row->args[1], PRINT));
		if (update_oldpwd(shell, current_dir) != 0)
			return (-1);
		if (update_pwd(shell) != 0)
			return (-1);
	}
	// make with args a separate function
	return (0);
}

// functions checks whether cd has an argument
// if cd has an argument it calls cd_no_args whcih moves the current directory to $HOME


// ---- issues --- /
// get malloc error for cd l, has to do with free_table
// oldpwd is updated when cd fails
// --> this should happen later, if cd fails than oldpwd should not be updated
