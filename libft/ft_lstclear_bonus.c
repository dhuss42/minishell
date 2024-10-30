/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:44:50 by dhuss             #+#    #+#             */
/*   Updated: 2024/03/27 11:27:19 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*next_node;

	if (!lst || !del)
		return ;
	temp = *lst;
	while (temp)
	{
		next_node = temp->next;
		(*del)(temp->content);
		free(temp);
		temp = next_node;
	}
	*lst = NULL;
}
