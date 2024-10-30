/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:57:04 by maustel           #+#    #+#             */
/*   Updated: 2023/10/20 11:41:23 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Adds the node ’new’ at the beginning of the list.
lst: The address of a pointer to the first link of a list. (head)
new: The address of a pointer to the node to be added to the list.*/

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new != NULL)
	{
		new->next = *lst;
		*lst = new;
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
// 	// ptr = head;
// 	// while (ptr->next != NULL)
// 	// 	ptr = ptr->next;
// 	// ptr->next = temp;

// 	// //--------insert node at the beginning
// 	// temp = malloc (sizeof(t_list));
// 	// temp->content = add;
// 	// temp->next = head;
// 	// head = temp;

// 	ft_lstadd_front(&head, temp);
// 	ptr = head;
// 	while (ptr)
// 	{
// 		printf("%s\n", ptr->content);
// 		ptr = ptr->next;
// 	}

// 	return (0);
// }
