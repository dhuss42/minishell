/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:46:10 by maustel           #+#    #+#             */
/*   Updated: 2023/10/25 10:28:53 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Deletes the whole list.
Deletes and frees the given node and every successor of that node,
using the function ’del’ and free(3).
Finally, the pointer to the list must be set to NULL.
lst: The address of a pointer to a node.
del: The address of the function used to delete the content of the node.*/

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*curr;
	t_list	*nxt;

	if (!lst || !*lst || !del)
		return ;
	curr = *lst;
	while (curr != NULL)
	{
		nxt = curr->next;
		del (curr->content);
		free (curr);
		curr = nxt;
	}
	*lst = NULL;
}

// int main()
// {
// 	char	*c1 = strdup("Hallo");
// 	char	*c2 = strdup("du");
// 	char	*c3 = strdup("Amsel");
// 	// char	add[] = "BUUUUH!";

// 	t_list *head = NULL;
// 	head = malloc (sizeof(t_list));
// 	head->content = c1;
// 	head->next = NULL;

// 	t_list *curr = malloc (sizeof(t_list));
// 	curr->content = c2;
// 	curr->next = NULL;
// 	head->next = curr;

// 	curr = malloc (sizeof(t_list));
// 	curr->content = c3;
// 	curr->next = NULL;
// 	head->next->next = curr;

// 	t_list *ptr = NULL;
// 	ptr = head;
// 	while (ptr)
// 	{
// 		printf("%s\n", ptr->content);
// 		ptr = ptr->next;
// 	}

// 	ptr = head;
// 	ft_lstclear(&ptr, &free);
// 	ptr = head;
// 	while (ptr && ptr->content)
// 	{
// 		printf("%s\n", ptr->content);
// 		ptr = ptr->next;
// 	}

// 	return (0);
// }
