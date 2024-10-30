/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:39:05 by maustel           #+#    #+#             */
/*   Updated: 2023/10/20 12:28:05 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Counts the number of nodes in a list.
lst: The beginning of the list.*/

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

// int main()
// {
// 	char	c1[] = "Hallo";
// 	char	c2[] = "du";
// 	char	c3[] = "Amsel";
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

// 	printf("%d\n", ft_lstsize(head));

// 	return (0);
// }
