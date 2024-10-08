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

#ifndef MINISHELL_EICHHOERNCHEN_H
# define MINISHELL_EICHHOERNCHEN_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include "libft/libft.h"
#include <string.h>

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

typedef struct s_command
{
	char	**args;
	char	**filename;
	char	**red_symbol;
	int		count_pipes; // maybe this needs to be somehwere else, could count the amount of pipes with ft_lstsize - 1
} t_command;

typedef struct s_trim
{
	size_t	i;
	size_t	j;
	size_t	len;
	bool	isspace;
	char	*res;
} t_trim;

//-----------------lexer----------------//

char	**split_space_quotes(char *input);
t_list	*tokeniser(char **split_double_array);
void    syntax_errors(t_list *token_list);

//----------------parser----------------//
t_list   *parser(t_list *token_list);
int is_filename(token *current_token);
int is_redirection(token *current_token);


//----------free-stuf------------//
void	free_token(void *content);

//------------extra-shit-----------//
void	print_token(token *tok);
void	print_token_list(t_list *list);
void    print_table(t_list *table);

#endif