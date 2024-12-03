/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:16:11 by gapachec          #+#    #+#             */
/*   Updated: 2024/12/02 20:16:45 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_list	*ft_lstnew(char content)
{
	t_list	*new_list;

	new_list = malloc(sizeof(t_list));
	if (!new_list)
		return (NULL);
	new_list->c = content;
	new_list->next = NULL;
	return (new_list);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	total_size;
	size_t	i;

	total_size = nmemb * size;
	if (nmemb && total_size / nmemb != size)
		return (NULL);
	ptr = malloc(total_size);
	if (ptr != NULL)
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
