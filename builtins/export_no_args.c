/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:06:57 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/06 12:22:50 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

void	put_str_n(char *str, size_t n, size_t i)
{
	while (str[i] != '\0' && i < n)
		write(1, &str[i++], 1);
}

char	**allocate_sorted(t_shell *shell, char **sorted)
{
	shell->k = 0;
		while(shell->env[shell->k] != NULL)
			shell->k++;
		sorted = malloc(sizeof(char *) * (shell->k + 1));
		if (!sorted)
		{
			print_error(errno, NULL, PRINT);
			return (NULL);
		}
		shell->k = 0;
		while(shell->env[shell->k] != NULL)
		{
			sorted[shell->k] = ft_strdup(shell->env[shell->k]);
			if (!sorted[shell->k])
			{
				print_error(errno, NULL, PRINT);
				clear_all(sorted);
				return (NULL);
			}
			shell->k++;
		}
	sorted[shell->k] = NULL;
	return (sorted);
}

char **bubble_sort(t_shell *shell, char **sorted)
{
	size_t i;
	char	*tmp;

	i = 0;
	while (i < shell->k - 1)
	{
		shell->j = 0;
		while (shell->j < shell->k - i - 1)
		{
			if (strlen_equal(sorted[shell->j]) > strlen_equal(sorted[shell->j + 1]))
				shell->len = strlen_equal(sorted[shell->j]);
			else
				shell->len = strlen_equal(sorted[shell->j + 1]);
			if (ft_strncmp(sorted[shell->j], sorted[shell->j + 1], shell->len) > 0)
			{
				tmp = sorted[shell->j];
				sorted[shell->j] = sorted[shell->j + 1];
				sorted[shell->j + 1] = tmp;
			}
			shell->j++;
		}
		i++;
	}
	return (sorted);
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
	size_t  i;
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
				put_str_n(sorted[i], ft_strlen(sorted[i]), strlen_equal(sorted[i]) + 1);
				write(1, "\"", 2);
			}
			ft_printf("\n");
		i++;
	}
	clear_all(sorted);
	return (0);
}
