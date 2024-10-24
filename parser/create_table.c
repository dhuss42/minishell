/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:00:48 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/10 11:06:38 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_eichhoernchen.h"

t_command	*create_cmd_block(void)
{
	t_command	*new_cmd;

	new_cmd = NULL;
	new_cmd = malloc(sizeof(t_command));
	if (!new_cmd)
	{
		// print_error(errno, NULL);
		return (NULL);
	}
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

t_command	*allocate_cmd(t_command *new_cmd, t_list *tl_pos, t_shell *parsing)
{
	new_cmd->args = malloc(sizeof(char *) * (parsing->words + 1));
	if (!new_cmd->args)
	{
		// printf("I return after new_cmd->args malloc fail\n");
		free_table(parsing);
		// print_error(errno, NULL);
		return (NULL);
	}
	new_cmd->red_symbol = malloc(sizeof(char *) * (parsing->reds + 1));
	if (!new_cmd->red_symbol)
	{
		// printf("I return after new_cmd->red_symbol malloc fail\n");
		free_table(parsing);
		// print_error(errno, NULL);
		return (NULL);
	}
	new_cmd->filename = malloc (sizeof(char *) * (parsing->filenames + 1));
	if (!new_cmd->filename)
	{
		// printf("I return after new_cmd->filename malloc fail\n");
		free_table(parsing);
		// print_error(errno, NULL);
		return (NULL);
	}
	new_cmd = populate_cmd(new_cmd, tl_pos, parsing);
	if (!new_cmd)
	{
		// printf("I return after populate_cmd\n");
		return (NULL);
	}
	return (new_cmd);
}

int	create_table(t_shell *shell)
{
	t_list		*tmp;
	t_list		*tmp2;
	t_list		*new_node;
	t_command	*new_cmd;

	tmp = shell->list;
	shell->lines = count_lines_table(shell->list);
	while (shell->lines > 0 && tmp != NULL)
	{
		new_cmd = create_cmd_block();
		if (!new_cmd)
		{
			// printf("I return after create_cmd_block\n");
			return (-1);
		}
		new_node = ft_lstnew((void *)new_cmd);
		if (!new_node)
		{
			// printf("I return after ft_lstnew\n");
			// print_error(errno, NULL);
			return (-1);
		}
		tmp2 = tmp;
		set_to_zero(shell);
		nbr_words_redirections(shell, &tmp);
		new_cmd = allocate_cmd(new_cmd, tmp2, shell);
		if (!new_cmd)
		{
			// printf("I return after allocate_cmd\n");
			return (-1);
		}
		ft_lstadd_back(&shell->table, new_node);
		if (tmp == NULL)
			break ;
		tmp = tmp->next;
		shell->lines--;
	}
	// printf("I return after at the end of function\n");
	return (0);
}
