/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:06:57 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/19 12:10:29 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	put_str_n(char *str, size_t n, size_t i)
{
	while (str[i] != '\0' && i < n)
		write(1, &str[i++], 1);
}

char	**allocate_sorted(t_shell *shell, char **sorted)
{
	shell->k = 0;
	while (shell->env[shell->k] != NULL)
		shell->k++;
	sorted = safe_malloc(sizeof(char *) * (shell->k + 1));
	if (!sorted)
		return (NULL);
	shell->k = 0;
	while (shell->env[shell->k] != NULL)
	{
		sorted[shell->k] = safe_ft_strdup(shell->env[shell->k]);
		if (!sorted[shell->k])
			return (clear_all(sorted), NULL);
		shell->k++;
	}
	sorted[shell->k] = NULL;
	return (sorted);
}

char	**bubble_sort(t_shell *shell, char **res)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (i < shell->k - 1)
	{
		shell->j = 0;
		while (shell->j < shell->k - i - 1)
		{
			if (strlen_equal(res[shell->j])
				> strlen_equal(res[shell->j + 1]))
				shell->len = strlen_equal(res[shell->j]);
			else
				shell->len = strlen_equal(res[shell->j + 1]);
			if (ft_strncmp(res[shell->j], res[shell->j + 1], shell->len) > 0)
			{
				tmp = res[shell->j];
				res[shell->j] = res[shell->j + 1];
				res[shell->j + 1] = tmp;
			}
			shell->j++;
		}
		i++;
	}
	return (res);
}

char	**sorter(t_shell *shell)
{
	char	**sorted;

	sorted = NULL;
	sorted = allocate_sorted(shell, sorted);
	if (!sorted)
		return (NULL);
	sorted = bubble_sort(shell, sorted);
	return (sorted);
}

int	export_no_argument(t_shell *shell)
{
	size_t	i;
	char	**sorted;

	i = 0;
	sorted = sorter(shell);
	if (!sorted)
		return (-1);
	while (sorted[i] != NULL)
	{
		ft_printf("declare -x ");
		put_str_n(sorted[i], strlen_equal(sorted[i]) + 1, 0);
		if (has_equal(sorted[i]))
		{
			write(1, "\"", 1);
			put_str_n(sorted[i], ft_strlen(sorted[i]),
				strlen_equal(sorted[i]) + 1);
			write(1, "\"", 2);
		}
		ft_printf("\n");
		i++;
	}
	clear_all(sorted);
	return (0);
}
