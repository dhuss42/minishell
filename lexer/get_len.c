/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:18:04 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/27 15:28:43 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_len_ws(t_shell *nbr, char *str)
{
	nbr->len++;
	while (is_wspace(str[nbr->i]) && str[nbr->i] != '\0')
		nbr->i++;
}

void	get_len_quotes(t_shell *nbr, char *str, t_shell *shell)
{
	char	quotes[2];

	quotes[0] = str[nbr->i];
	quotes[1] = '\0';
	nbr->i++;
	nbr->len++;
	while (str[nbr->i] != quotes[0] && str[nbr->i] != '\0')
	{
		nbr->i++;
		nbr->len++;
	}
	if (str[nbr->i] == '\0')
	{
		shell->syntax_error = true;
		print_error(E_SYNTAXERROR, quotes, PRINT);
		return ;
	}
	if (str[nbr->i] == quotes[0])
	{
		nbr->i++;
		nbr->len++;
	}
}

void	get_len_special(t_shell *nbr, char *str)
{
	if (nbr->i != 0 && !is_wspace(str[nbr->i - 1])
		&& !is_special_no_quotes(str[nbr->i - 1]))
		nbr->len++;
	nbr->len ++;
	if (str[nbr->i + 1] != '\0' && !is_wspace(str[nbr->i + 1]))
		nbr->len++;
	nbr->i ++;
}

void	get_len_double_red(t_shell *nbr, char *str)
{
	if (nbr->i != 0 && !is_wspace(str[nbr->i - 1])
		&& !is_special_no_quotes(str[nbr->i - 1]))
		nbr->len++;
	nbr->len += 2;
	if (str[nbr->i + 2] != '\0' && !is_wspace(str[nbr->i + 2]))
		nbr->len++;
	nbr->i += 2;
}

size_t	get_len(char *str, t_shell *shell)
{
	t_shell	nbr;

	nbr.i = 0;
	nbr.len = 0;
	while (str[nbr.i] != '\0')
	{
		if (is_wspace(str[nbr.i]))
			get_len_ws(&nbr, str);
		else if (str[nbr.i] == '\'' || str[nbr.i] == '\"')
			get_len_quotes(&nbr, str, shell);
		else if ((str[nbr.i] == '<' && str[nbr.i + 1] == '<')
			|| (str[nbr.i] == '>' && str[nbr.i + 1] == '>'))
			get_len_double_red(&nbr, str);
		else if (is_special_no_quotes(str[nbr.i]))
			get_len_special(&nbr, str);
		else
		{
			nbr.len++;
			nbr.i++;
		}
	}
	return (nbr.len);
}
