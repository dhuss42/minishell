/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_eichhoernchen.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:40:51 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/21 15:59:14 by dhuss            ###   ########.fr       */
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


//----------------colors--------------//
#define RESET       "\033[0m"
#define BLACK       "\033[30m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"
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
} t_command;

typedef struct s_shell
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	len;
	size_t	lines;
	size_t	words;
	size_t	reds;
	size_t	filenames;
	t_list	*tmp;
	t_list	*table;
	bool	isspace;
	char	*res;
	char	quote;
} t_shell;

//-----------------loop----------------//


//-----------------lexer----------------//
t_list  *lexer(t_list *list);
char 	*trim_spaces(char *input);
size_t	get_len(char *str);
char	**split_space_quotes(char *input);
t_list	*tokeniser(char **split_double_array);
void	syntax_errors(t_list *token_list);

//----------------parser----------------//
t_list		*parser(t_list *token_list);
t_list		*create_table(t_list *token_list, t_shell *parsing);
t_command	*populate_cmd(t_command *new_cmd, t_list *tl_pos, t_shell *parsing);

//----------------expansion----------------//
t_list *expansion(t_list *table, char **env);
bool	iterate_table(t_list *table, char **env);
void	get_expanded(char *variable, char **env, t_command *row, t_shell *expand);
void	quotes(t_command *row, t_shell *expand, char **env);
char	*tmp_dollar(t_command *row, t_shell *expand);
bool	should_expand(char *str, size_t k);
void	remove_quotes(t_list *table);

//----------------helpers----------------//

	//--> lexer
bool	is_special(char input);
bool	is_special_no_quotes(char input);
bool	is_wspace(char input);

	//--> parser
int		is_filename(token *current_token);
int		is_redirection(token *current_token);
void	set_to_zero(t_shell *nbr);

	//--> expansion
bool	is_quotes(char c);
bool	contains_dollar(char *str, size_t i);

//----------free-stuf------------//
void	free_token(void *content);
void	clear_all(char **to_clear);
void	free_table(t_shell *parsing);

//------------extra-shit-----------//
void	print_token(token *tok);
void	print_token_list(t_list *list);
void	print_table(t_list *table);

#endif