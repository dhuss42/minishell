/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:03:35 by dhuss             #+#    #+#             */
/*   Updated: 2024/11/27 15:26:17 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	populate_red_array(t_shell *par, t_token *ct, t_command *cmd)
{
	int	len;

	len = ft_strlen(ct->input);
	cmd->red_symbol[par->i] = safe_malloc(sizeof(char) * (len + 1));
	if (!cmd->red_symbol[par->i])
	{
		free_command(cmd);
		return (-1);
	}
	ft_strlcpy(cmd->red_symbol[par->i], ct->input, len + 1);
	return (0);
}

int	populate_filename_array(t_shell *par, t_token *nt, t_command *cmd)
{
	int	len;

	len = ft_strlen(nt->input);
	cmd->filename[par->i] = safe_malloc(sizeof(char) * (len + 1));
	if (!cmd->filename[par->i])
	{
		free_command(cmd);
		return (-1);
	}
	ft_strlcpy(cmd->filename[par->i], nt->input, len + 1);
	par->tmp = par->tmp->next;
	return (0);
}

int	populate_args_array(t_shell *pa, t_token *ct, t_command *cmd)
{
	int	len;

	len = ft_strlen(ct->input);
	cmd->args[pa->j] = safe_malloc(sizeof(char) * (len + 1));
	if (!cmd->args[pa->j])
	{
		free_command(cmd);
		return (-1);
	}
	if (cmd->args[pa->j] == cmd->args[0])
		ft_strlcpy_lowercase(cmd->args[pa->j], ct->input, len + 1);
	else
		ft_strlcpy(cmd->args[pa->j], ct->input, len + 1);
	pa->j++;
	return (0);
}

int	pop_doub_arr(t_shell *parsing, t_token *ct, t_token *nt, t_command *new_cmd)
{
	if (is_redirection(ct))
	{
		if (populate_red_array(parsing, ct, new_cmd) == -1)
			return (-1);
		if (is_filename(nt))
		{
			if (populate_filename_array(parsing, nt, new_cmd) == -1)
				return (-1);
		}
		parsing->i++;
	}
	else
	{
		if (populate_args_array(parsing, ct, new_cmd) == -1)
			return (-1);
	}
	return (0);
}

// this function checks if the current node
// is a redirection symbol and allocates enough
// memory for it in the struct(table)‚
// copies the symbol in struct at index
// i (the same index as the filename later on)
// this part allocates enough memory in the table for the filename
// the file name is saved at the same index as the redirection symbol
// needs and additional itteration

t_command	*populate_cmd(t_command *new_cmd, t_list *tl_pos, t_shell *parsing)
{
	t_token	*current_token;
	t_token	*next_token;

	parsing->i = 0;
	parsing->j = 0;
	parsing->tmp = tl_pos;
	while (parsing->tmp != NULL)
	{
		current_token = (t_token *)parsing->tmp->content;
		if (parsing->tmp->next != NULL)
			next_token = (t_token *)parsing->tmp->next->content;
		if (current_token->type == TOKEN_PIPE)
			break ;
		if (pop_doub_arr(parsing, current_token, next_token, new_cmd) == -1)
			return (NULL);
		parsing->tmp = parsing->tmp->next;
	}
	new_cmd->args[parsing->j] = NULL;
	new_cmd->red_symbol[parsing->i] = NULL;
	new_cmd->filename[parsing->i] = NULL;
	return (new_cmd);
}
