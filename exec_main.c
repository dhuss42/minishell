/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:09:13 by maustel           #+#    #+#             */
/*   Updated: 2024/10/25 10:09:13 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/*
!!! initialize everyting in beginning before lexer
*/
t_list	*create_example(char *args, char* red, char *files)
{
	t_list	*new;
	t_command *ex = malloc(sizeof(t_command));

	ex->args = NULL;
	ex->filename = NULL;
	ex->red_symbol = NULL;
	ex->path = NULL;
	ex->heredoc_file_path = NULL;
	ex->args = ft_split(args, ' ');
	ex->filename = ft_split(files, ' ');
	ex->red_symbol = ft_split(red, ' ');
	new = ft_lstnew((void *) ex);
	return (new);
}

int main (int argc, char **argv, char **envp)
{
	t_exec test;
	t_list *table;
	// t_command	*current_cmd;
	table = NULL;
	t_list	*second = NULL;
	// t_list	*third = NULL;
	// t_list	*fourth = NULL;

	table = create_example("echo outiout", "<< <", "a amsel");
	second = create_example("cat", "<<", "b");
	ft_lstadd_back(&table, second);
	// third = create_example("cat", "<", "libft");
	// ft_lstadd_back(&table, third);
	// fourth = create_example("grep a", "<", "libft");
	// ft_lstadd_back(&table, fourth);
	// current_cmd = (t_command *) temp->content;
	// printf("temp\nargs: %s\nfiles: %s\nsymbol: %s\n\n", current_cmd->args[0], current_cmd->filename[0], current_cmd->red_symbol[0]);
	// current_cmd = (t_command *) table->content;
	// printf("table\nargs: %s\nfiles: %s\nsymbol: %s\n\n", current_cmd->args[0], current_cmd->filename[0], current_cmd->red_symbol[0]);

	if (executor (envp, table, &test))
		return (print_error(0, NULL, NOTPRINT));
	// printf ("[Exit code: %d]\n", test.exit_code);
	// printf ("[final infile: %s]\n", test.final_infile);
	// printf ("[final outfile: %s]\n", test.final_outfile);
	// printf ("[final in red: %s]\n", test.final_in_red);
	// printf ("[final out red: %s]\n", test.final_out_red);
	free_table(table);
	return (print_error(0, NULL, NOTPRINT));
	(void)argc;
	(void)argv;
	return (0);
}
