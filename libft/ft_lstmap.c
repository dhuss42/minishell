/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 11:17:12 by maustel           #+#    #+#             */
/*   Updated: 2023/10/25 15:40:56 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Iterates the list ’lst’ and applies the function ’f’ on the content of each
node.
Creates a new list resulting of the successive applications of the function ’f’
The ’del’ function is used to delete the content of a node if needed.
lst: The address of a pointer to a node.
f: The address of the function used to iterate on the list.
del: The address of the function used to delete the content of a node if
needed.
Return value: The new list. NULL if the allocation fails.*/

int	ft_delete(t_list *lstnew, void (*del)(void *), void *contnew)
{
	if (!contnew)
	{
		del (contnew);
		ft_lstclear (&lstnew, del);
		return (0);
	}
	return (1);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lstnew;
	t_list	*nodenew;
	void	*contnew;

	if (!f || !del)
		return (NULL);
	lstnew = NULL;
	nodenew = NULL;
	while (lst)
	{
		contnew = f (lst->content);
		if (!ft_delete(lstnew, del, contnew))
			return (NULL);
		nodenew = ft_lstnew (contnew);
		if (!nodenew)
		{
			del (contnew);
			ft_lstclear (&lstnew, del);
			return (NULL);
		}
		ft_lstadd_back (&lstnew, nodenew);
		lst = lst->next;
	}
	return (lstnew);
}

// void	*f_test(void *str)
// {
// 	str = strdup("***");
// 	return (str);
// }

// int main()
// {
// 	t_list	*ptr;
// 	t_list	*ptrnew;

// 	ptr = ft_lstnew ("hallo");
// 	ft_lstadd_back (&ptr, ft_lstnew("kleiner"));
// 	ft_lstadd_back (&ptr, ft_lstnew("Hamster"));

// 	ptrnew = ptr;
// 	while (ptrnew)
// 	{
// 		printf ("%s\n", ptrnew->content);
// 		ptrnew = ptrnew->next;
// 	}

// 	ptrnew = ft_lstmap (ptr, f_test, &free);
// 	while (ptrnew)
//     {
//         printf("%s\n", (char *)ptrnew->content);
//         ptrnew = ptrnew->next;
//     }
//     // Clear the new list
//     ft_lstclear(&ptrnew, *free);

// 	return (0);
// }
