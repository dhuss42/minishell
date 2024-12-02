/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:40:51 by dhuss             #+#    #+#             */
/*   Updated: 2024/12/01 13:06:11 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "minishell_structs.h"

# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdarg.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>

//----------------colors--------------//
# define RESET       "\033[0m"
# define BLACK       "\033[30m"
# define RED         "\033[31m"
# define GREEN       "\033[32m"
# define YELLOW      "\033[33m"
# define BLUE        "\033[34m"
# define MAGENTA     "\033[35m"
# define CYAN        "\033[36m"
# define WHITE       "\033[37m"

//-------------------environment------------------//
int			copy_env(char **env, t_shell *shell);
int			shlvl(t_shell *shell);

//-----------------builtins----------------//
int			ft_pwd(void);
int			ft_env(t_shell *shell);
int			ft_export(t_shell *shell, t_command *row);
int			export_with_args(t_shell *shell, t_command *row);
int			export_no_argument(t_shell *shell);
int			ft_echo(t_shell *shell, t_command *row);
void		echo_expanded(t_shell *shell, t_command *row);
int			ft_unset(t_shell *shell, t_command *row);
int			ft_exit(t_shell *shell, t_command *row);
int			ft_cd(t_shell *shell, t_command *row);

//-----------------lexer----------------//
void		lexer(t_shell *shell, char *input);
char		*trim_spaces(char *input, t_shell *shell);
size_t		get_len(char *str, t_shell *shell);
char		**split_space_quotes(char *input);
t_list		*tokeniser(char **split_double_array);
bool		syntax_errors(t_list *token_list);

//----------------parser----------------//
void		parser(t_shell *shell);
int			create_table(t_shell *shell, t_list *new_node,
				t_command *cmd, t_list *tmp);
t_command	*populate_cmd(t_command *new_cmd, t_list *tl_pos, t_shell *parsing);

//----------------expansion----------------//
void		expansion(t_shell *shell, char **env);
int			iterate_table(t_list *table, char **env);
int			get_expanded(char *variable, char **env, t_command *row,
				t_shell *expand);
char		*compare_with_env(char *variable, char **env, char *exp);
int			get_exit_code(char *tmp, t_command *row, t_shell *expand);
int			remove_quotes(t_list *table, t_shell *shell);
int			process_quotes(char **array, t_shell *expand);

//-------------------utils------------------//
void		*safe_malloc(size_t size);
char		*safe_ft_substr(const char *s, unsigned int start, size_t len);
char		*safe_ft_strdup(const char *s);
char		*safe_ft_strtrim(char *s, const char *set);
void		*safe_ft_calloc(size_t count, size_t size);

//----------------helpers----------------//
	//--> builtins
bool		has_equal(const char *str);
bool		valid_key_name(char *str);
int			key_exists(char **env, char *key);
char		**set_to_null(char **tmp, size_t len);
int			get_len_new_env(char **env, t_command *row, size_t i);
int			update_pwd(t_shell *shell);
int			update_oldpwd(t_shell *shell, char *content);
char		**duplicate_double_ptr(char **double_ptr);
char		*search_env(char **env, char *key);

	//--> lexer
bool		is_special(char input);
bool		is_special_no_quotes(char input);
bool		is_wspace(char input);

	//--> parser
int			is_filename(t_token *current_token);
int			is_redirection(t_token *current_token);
void		set_to_zero(t_shell *nbr);
size_t		ft_strlcpy_lowercase(char *dst, const char *src, size_t dstsize);

	//--> expansion
bool		is_quotes(char c);
bool		contains_dollar(char *str, size_t i);
size_t		strlen_equal(char *str);
int			get_int_length(int num);

//----------------errors--------------------------
int			print_error(int err_no, char *str, int print);
int			custom_error_print_2(int err_no);

//-----------------executor-----------------------
char		*get_path(char *cmd, char **envp);
void		free_paths(char **split_paths, char **append, char *big_path);
int			check_files(t_command *row);
int			exec_redirections(t_command *row);
void		free_double(char **to_free);
int			free_row(t_command *example);
int			get_check_path(t_command *row, char **envp);
int			free_table(t_list *table);
int			handle_heredoc(t_list *table, char **env);
char		*heredoc_expansion(char *line, char **env);
int			heredoc_parent(pid_t pid);
char		*generate_file_path(int id);
size_t		get_len_exp_hd(char *line, char *exp, size_t index);
int			redirect_input(t_command row, int *fd);
int			redirect_output(t_command row, int *fd);
int			redirect_output_pipe(int *fd);
void		reset_redirections(t_command *row);
int			executor(t_shell *shell);
int			pipechain_loop(t_shell *shell);
int			pipe_parent(t_shell *shell, int nbr_pipes);
void		free_child_exit(t_shell *shell, int exit_code);
int			init_fd_pid(t_shell *shell, int nbr_pipes);
void		free_fd_pid(t_shell *shell, int nbr_pipes);
void		set_original_std(t_command *row);

//-------------signals---------
void		handle_signals(int is_child);
void		init_terminal(void);

//----------free-stuf------------//
void		free_token(void *content);
void		clear_all(char **to_clear);
void		memory_parser(t_shell *parsing, t_command *cmd);
void		free_table_parser(t_shell *parsing);
void		free_command(t_command *cmd);
void		free_three(char *str, char *str2, char *str3);
void		free_minishell(t_shell *shell, char *input);

//------------extra-shit-----------//
void		print_token(t_token *tok);
void		print_token_list(t_list *list);
void		print_table(t_shell *shell);
int			check_builtins(t_shell *shell, t_command *row);

#endif
