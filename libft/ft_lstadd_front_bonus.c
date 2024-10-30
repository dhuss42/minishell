/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:51:42 by dhuss             #+#    #+#             */
/*   Updated: 2024/03/27 11:27:13 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new == NULL || lst == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}

/* int main(void)
{
    t_list *head = NULL;
    t_list *new_element1 = ft_lstnew("First element");
    t_list *new_element2 = ft_lstnew("Second element");
    t_list *new_element3 = ft_lstnew("Third element");
    ft_lstadd_front(&head, new_element3);
    ft_lstadd_front(&head, new_element2);
    ft_lstadd_front(&head, new_element1);
    t_list *current = head;
    while (current != NULL)
    {
        printf("%s\n", (char *)current->content);
        current = current->next;
    }
    while (head != NULL)
    {
        t_list *tmp = head;
        head = head->next;
        free(tmp);
    }
    return (0);
} */
