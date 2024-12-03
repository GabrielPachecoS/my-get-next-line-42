/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:37:50 by gapachec          #+#    #+#             */
/*   Updated: 2024/12/02 20:38:39 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstnew(char content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->c = content;
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total_size;
	void	*ptr;
	size_t	i;

	total_size = nmemb * size;
	if (nmemb && total_size / nmemb != size)
		return (NULL);
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	else
	{
		i = 0;
		while (i < total_size)
		{
			((unsigned char *)ptr)[i] = 0;
			i++;
		}
	}
	return (ptr);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*first;

	first = *lst;
	if (!lst)
		return ;
	while (first)
	{
		temp = first->next;
		del(first);
		first = temp;
	}
	*lst = NULL;
}
