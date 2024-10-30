/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:39:17 by dhuss             #+#    #+#             */
/*   Updated: 2024/03/27 11:05:46 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}
/*
#include <stdio.h>

int main(void)
{
	t_list	*head = ft_lstnew("Zero");
	t_list	*one = ft_lstnew("First Element");
	t_list	*two = ft_lstnew("Second Element");
	t_list	*three = ft_lstnew("Third Element");
	t_list	*last;
	ft_lstadd_front(&head, three);
	ft_lstadd_front(&head, two);
	ft_lstadd_front(&head, one);
	last = ft_lstlast(head);
	if (last != NULL)
		printf("Last element of the list: %s\n", (char *)last->content);
	else
		printf("List is empty");
	return (0);
} */
