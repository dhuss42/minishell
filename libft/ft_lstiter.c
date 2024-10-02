/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:42:41 by maustel           #+#    #+#             */
/*   Updated: 2023/10/25 15:12:57 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Iterates the list ’lst’ and applies the function ’f’ on the content
of each node.
lst: The address of a pointer to a node.
f: The address of the function used to iterate on the list.*/

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f (lst->content);
		lst = lst->next;
	}
}

// void	f_test(void *ptr)
// {
// 	int	i = 0;
// 	char	*str = (char *) ptr;
// 	while (str[i])
// 	{
// 		str[i] = '*';
// 		i++;
// 	}
// }

// int main()
// {
// 	char	*c1 = strdup("Hallo");
// 	char	*c2 = strdup("du");
// 	char	*c3 = strdup("Amsel");
// 	// char	add[] = "BUUUUH!";

// 	t_list *head = NULL;
// 	head = ft_lstnew (c1);
// 	ft_lstadd_back (&head, ft_lstnew (c2));
// 	ft_lstadd_back (&head, ft_lstnew (c3));
// 	t_list *ptr = NULL;
// 	ptr = head;
// 	while (ptr)
// 	{
// 		printf("%s\n", ptr->content);
// 		ptr = ptr->next;
// 	}

// 	ptr = head;
// 	ft_lstiter(ptr, f_test);
// 	while (ptr)
// 	{
// 		printf("%s\n", ptr->content);
// 		ptr = ptr->next;
// 	}

// 	return (0);
// }
