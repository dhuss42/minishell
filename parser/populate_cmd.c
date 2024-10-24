/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:03:35 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/10 11:07:06 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_eichhoernchen.h"

int	populate_red_array(t_shell *parsing, token* current_token, t_command *new_cmd)
{
	new_cmd->red_symbol[parsing->i] = malloc(sizeof(char) * (ft_strlen(current_token->input) + 1));
	if (!new_cmd->red_symbol[parsing->i])
	{
		free_table(parsing);
		// printf("I return issue populate_red_array\n");
		// print_error(errno, NULL);
		return (-1);
	}
	ft_strlcpy(new_cmd->red_symbol[parsing->i], current_token->input, ft_strlen(current_token->input) + 1);
	return (0);
}

int	populate_filename_array(t_shell *parsing, token* next_token, t_command *new_cmd)
{
	new_cmd->filename[parsing->i] = malloc(sizeof(char) * (ft_strlen(next_token->input) + 1));
	if (!new_cmd->filename[parsing->i])
	{
		free_table(parsing);
		// printf("I return issue populate_filename_array\n");
		// print_error(errno, NULL);
		return (-1);
	}
	ft_strlcpy(new_cmd->filename[parsing->i], next_token->input, ft_strlen(next_token->input) + 1);
	parsing->tmp = parsing->tmp->next;
	return (0);
}

int	populate_args_array(t_shell *parsing, token* current_token, t_command *new_cmd)
{
	new_cmd->args[parsing->j] = malloc(sizeof(char) * ft_strlen(current_token->input) + 1);
	if (!new_cmd->args[parsing->j])
	{
		free_table(parsing);
		// printf("I return issue populate_args_array\n");
		// print_error(errno, NULL);
		return (-1);
	}
	ft_strlcpy(new_cmd->args[parsing->j], current_token->input, ft_strlen(current_token->input) + 1);
	parsing->j++;
	return (0);
}

int	populate_double_arrays(t_shell *parsing, token *current_token, token *next_token, t_command *new_cmd)
{
	if (is_redirection(current_token))
	{
		if (populate_red_array(parsing, current_token, new_cmd) == -1)
			return (-1);
		if (populate_filename_array(parsing, next_token, new_cmd) == -1)
			return (-1);
		parsing->i++;
	}
	else
	{
		if (populate_args_array(parsing, current_token, new_cmd) == -1)
			return (-1);
	}
	return (0);
}

// this function checks if the current node is a redirection symbol and allocates enough memory for it in the struct(table)‚
// copies the symbol in struct at index i (the same index as the filename later on)
// this part allocates enough memory in the table for the filename
// the file name is saved at the same index as the redirection symbol
// needs and additional itteration

t_command	*populate_cmd(t_command *new_cmd, t_list *tl_pos, t_shell *parsing)
{
	token	*current_token;
	token	*next_token;

	parsing->i = 0;
	parsing->j = 0;
	parsing->tmp = tl_pos;
	while(parsing->tmp != NULL)
	{
		current_token = (token *)parsing->tmp->content;
		if (parsing->tmp->next != NULL)
			next_token = (token *)parsing->tmp->next->content;
		if (current_token->type == TOKEN_PIPE)
			break ;
		if (populate_double_arrays(parsing, current_token, next_token, new_cmd) == -1)
			return (NULL);
		parsing->tmp = parsing->tmp->next;
	}
	new_cmd->args[parsing->j] = NULL;
	new_cmd->red_symbol[parsing->i] = NULL;
	new_cmd->filename[parsing->i] = NULL;
	return (new_cmd);
}

