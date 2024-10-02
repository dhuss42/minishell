/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:56:28 by maustel           #+#    #+#             */
/*   Updated: 2023/10/20 14:18:19 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Returns the last node of the list.
lst: The beginning of the list.*/

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*ptr;

	if (!lst)
		return (NULL);
	ptr = lst;
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
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
// 	while (ptr->next != NULL)
// 		ptr = ptr->next;
// 	ptr->next = temp;

// 	//--------insert node at the beginning
// 	temp = malloc (sizeof(t_list));
// 	temp->content = add;
// 	temp->next = head;
// 	head = temp;
// 	ptr = head;
// 	while (ptr)
// 	{
// 		printf("%s\n", ptr->content);
// 		ptr = ptr->next;
// 	}
// 	printf("\n%s\n", (char *) ft_lstlast(head)->content);

// 	return (0);
// }
