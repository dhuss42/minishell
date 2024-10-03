/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:40:51 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/02 17:29:44 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include "libft/libft.h"

//----------------structs--------------//

typedef enum
{
	TOKEN_PIPE,
	TOKEN_REDIN,
	TOKEN_REDOUT,
	TOKEN_HEREDOC,
	TOKEN_REDAPPEND,
	TOKEN_SQUOTES,
	TOKEN_DQUOTES,
	TOKEN_ENVVAR,
	TOKEN_EXITSTATUS,
	TOKEN_ARGS,
	TOKEN_WORD,
} token_type;

typedef struct s_token
{
	token_type type;
	char *input;
} token;

typedef struct s_trim
{
	size_t	i;
	size_t	j;
	size_t	len;
	bool	isspace;
	char	*res;
} t_trim;

//------------------------------------//

char	**split_space_quotes(char *input);
t_list	*tokeniser(char **split_double_array);

void	print_token(token *tok);
void	print_token_list(t_list *list);
void	free_token(void *content);

#endif