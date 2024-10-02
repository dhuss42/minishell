/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:04:00 by maustel           #+#    #+#             */
/*   Updated: 2023/10/26 11:24:23 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Adds the node ’new’ at the end of the list.
lst: The address of a pointer to the first link of a list.
new: The address of a pointer to the node to be added to the list.*/

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ptr;

	if (new)
	{
		if (*lst == NULL)
		{
			*lst = new;
			new->next = NULL;
			return ;
		}
		ptr = ft_lstlast(*lst);
		if (!ptr)
			return ;
		ptr->next = new;
	}
}

// int main()
// {
// 	char	c1[] = "Hallo";
// 	char	c2[] = "du";
// 	char	c3[] = "Amsel";
// 	char	add[] = "BUUUUH!";

// 	t_list *head = NULL;
// 	head = malloc (sizeof(t_list));
// 	head->content = c1;
// 	head->next = NULL;

// 	t_list *current = malloc (sizeof(t_list));
// 	current->content = c2;
// 	current->next = NULL;
// 	head->next = current;

// 	current = malloc (sizeof(t_list));
// 	current->content = c3;
// 	current->next = NULL;
// 	head->next->next = current;

// 	t_list *ptr = NULL;
// 	//------insert node at the end
// 	t_list *temp = malloc (sizeof(t_list));
// 	temp->content = add;
// 	temp->next = NULL;
// 	ptr = head;
// 	ft_lstadd_back(&ptr, temp);

// 	// ptr = head;
// 	while (ptr)
// 	{
// 		printf("%s\n", ptr->content);
// 		ptr = ptr->next;
// 	}

// 	return (0);
// }
