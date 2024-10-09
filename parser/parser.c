/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:01:02 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/09 17:05:12 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_eichhoernchen.h"

t_command	*create_cmd_block(void)
{
	t_command	*new_cmd;

	new_cmd = NULL;
	new_cmd = malloc(sizeof(t_command));
	if (!new_cmd)
		return (NULL);
	new_cmd->args = NULL;
	new_cmd->filename = NULL;
	new_cmd->red_symbol = NULL;
	return (new_cmd);
}

size_t	count_lines_table(t_list *token_list)
{
	t_list	*tmp;
	size_t	lines;
	token	*current_token;

	tmp = token_list;
	lines = 0;
	while(tmp != NULL)
	{
		current_token = (token *)tmp->content;
		if (current_token->type == TOKEN_PIPE)
			lines++;
		tmp = tmp->next;
	}
	return (lines + 1);
}

void	nbr_words_redirections(t_shell *nbr, t_list **token_list)
{
	t_list	*tmp;
	token	*current_token;

	tmp = *token_list;
	while (tmp != NULL)
	{
		current_token = (token *)tmp->content;
		if (current_token->type == TOKEN_PIPE)
			break ;
		if (is_redirection(current_token))
		{
			nbr->reds++;
			if (tmp->next != NULL)
			{
				nbr->filenames++;
				tmp = tmp->next;
			}
		}
		else
			nbr->words++;
		tmp = tmp->next;
	}
	*token_list = tmp;
}

void	free_table(t_shell *parsing)
{
	t_list	*tmp;
	t_list	*next;
	t_command *cmd;

	tmp = parsing->table;
	while (tmp != NULL)
	{
		cmd = (t_command*)tmp->content;
		if (cmd)
		{
			if (cmd->args)
				clear_all(cmd->args);
			if (cmd->filename)
				clear_all(cmd->filename);
			if (cmd->red_symbol)
				clear_all(cmd->red_symbol);
			free(cmd);
		}
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	parsing->table = NULL;
}

t_command	*allocate_cmd(t_command *new_cmd, t_list *tl_pos, t_shell *parsing)
{
	new_cmd->args = malloc(sizeof(char *) * (parsing->words + 1));
	if (!new_cmd->args) // call the function to free everything
	{
		free_table(parsing);
		return (NULL);
	}
	new_cmd->red_symbol = malloc(sizeof(char *) * (parsing->reds + 1));
	if (!new_cmd->red_symbol)
	{
		free_table(parsing);
		return (NULL);
	}
	new_cmd->filename = malloc (sizeof(char *) * (parsing->filenames + 1));
	if (!new_cmd->filename) // what if we are in the second line of the table and have an error (free the remaining table)
	{
		free_table(parsing);
		return (NULL);
	}
	new_cmd = populate_cmd(new_cmd, tl_pos, parsing);
	return (new_cmd);
}

t_list	*create_table(t_list *token_list, t_shell *parsing)
{
	t_list		*tmp;
	t_list		*tmp2;
	t_list		*new_node;
	t_command	*new_cmd;

	tmp = token_list;
	parsing->lines = count_lines_table(token_list);
	while (parsing->lines > 0 && tmp != NULL)
	{
		new_cmd = create_cmd_block();
		new_node = ft_lstnew((void *)new_cmd);
		tmp2 = tmp;
		set_to_zero(parsing);
		nbr_words_redirections(parsing, &tmp);
		new_cmd = allocate_cmd(new_cmd, tmp2, parsing);
		ft_lstadd_back(&parsing->table, new_node);
		if (tmp == NULL)
			break ;
		tmp = tmp->next;
		parsing->lines--;
	}
	return (parsing->table);
}

t_list	*parser(t_list *token_list)
{
	t_shell	parsing;

	parsing.table = NULL;
	parsing.table = create_table(token_list, &parsing);
	print_table(parsing.table);

	free_table(&parsing); // just here for leak check
	return (parsing.table);
}

// Heredoc works with cmd before it


// < hello | wc -l | grep a >> outfile >> out
// ls -la | cat -e | cat -e
// echo $PATH | tr : '\n'

// next steps
//	split functions into multiple files, store them in a way that makes sense
//	handle the freeing of everything upon error