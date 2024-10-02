/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:47:33 by maustel           #+#    #+#             */
/*   Updated: 2023/10/20 16:45:31 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Takes as a parameter a node and frees the memory of the node’s content using
the function ’del’ given as a parameter and free the node.
The memory of ’next’ must not be freed.
lst: The node to free.
del: The address of the function used to delete the content.*/

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!del || !lst)
		return ;
	del (lst->content);
	free(lst);
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

// 	t_list *current = malloc (sizeof(t_list));
// 	current->content = c2;
// 	current->next = NULL;
// 	head->next = current;

// 	current = malloc (sizeof(t_list));
// 	current->content = c3;
// 	current->next = NULL;
// 	head->next->next = current;

// 	t_list *ptr = NULL;
// 	ptr = head;
// 	while (ptr)
// 	{
// 		printf("%s\n", ptr->content);
// 		ptr = ptr->next;
// 	}

// 	ptr = head->next;
// 	ft_lstdelone(ptr, &free);
// 	ptr = head;
// 	while (ptr)
// 	{
// 		printf("%s\n", ptr->content);
// 		ptr = ptr->next;
// 	}

// 	return (0);
// }
