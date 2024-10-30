/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:56:40 by maustel           #+#    #+#             */
/*   Updated: 2023/10/19 16:24:14 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Allocates (with malloc(3)) and returns a new node.
The member variable ’content’ is initialized with
the value of the parameter ’content’. The variable
’next’ is initialized to NULL.
Return value: The new node*/

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc (sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

// int main ()
// {
// 	char	*cont = "hello";
// 	t_list *node = ft_lstnew(cont);
// 	if (node)
// 	{
// 		printf("Node created\n");
// 		printf("Node content: %s\n", (char *) node->content);
// 	}
// 	free (node);
// 	return (0);
// }
