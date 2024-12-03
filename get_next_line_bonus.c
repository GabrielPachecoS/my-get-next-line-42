/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapachec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:14:36 by gapachec          #+#    #+#             */
/*   Updated: 2024/12/02 20:18:49 by gapachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static ssize_t	count_line_len(t_list *t_char, char n)
{
	ssize_t		len;
	t_list		*t_temp;

	len = 0;
	t_temp = t_char;
	if (!n)
	{
		if (t_temp && !t_temp->next)
			return (1);
		while (t_temp)
		{
			len++;
			t_temp = t_temp->next;
		}
		return (++len);
	}
	while (t_temp && t_temp->c != n)
	{
		len++;
		t_temp = t_temp->next;
	}
	if (t_temp && t_temp->c == n)
		len++;
	return (len);
}

static char	*create_new_line(t_list **t_char_node)
{
	ssize_t	i;
	t_list	*t_new_node;
	char	*new_line;
	ssize_t	len;

	t_new_node = *t_char_node;
	i = 0;
	len = count_line_len(*t_char_node, '\n');
	new_line = ft_calloc(sizeof(char), len + 1);
	while (t_new_node && t_new_node->c != '\n')
	{
		new_line[i++] = t_new_node->c;
		t_new_node = t_new_node->next;
		free(*t_char_node);
		*t_char_node = t_new_node;
	}
	if (!t_new_node)
	{
		new_line[i] = '\0';
		return (new_line);
	}
	new_line[i] = t_new_node->c;
	*t_char_node = t_new_node->next;
	free(t_new_node);
	return (new_line);
}

static void	create_new_node(int fd, char *buff, ssize_t rd, t_list	**t_char)
{
	ssize_t	break_line;
	ssize_t	i;

	break_line = 0;
	while (rd > 0)
	{
		i = 0;
		while (buff[i])
		{
			if (buff[i] == '\n')
				break_line = 1;
			ft_lstadd_back(&*t_char, ft_lstnew(buff[i++]));
		}
		if (break_line)
			break ;
		rd = read(fd, buff, BUFFER_SIZE);
		if (rd == -1)
		{
			ft_lstclear(t_char, free);
			free(buff);
			return ;
		}
		buff[rd] = '\0';
	}
	free(buff);
}

char	*get_next_line(int fd)
{
	char			*buffer;
	t_list static	*t_char_node[1024];
	ssize_t			r;

	if (fd < 0 || fd > 1024)
		return (NULL);
	r = 0;
	buffer = ft_calloc(sizeof (char), (BUFFER_SIZE + 1));
	r = read(fd, buffer, BUFFER_SIZE);
	if (r == -1)
		ft_lstclear(&t_char_node[fd], free);
	if ((!buffer || r <= 0 || BUFFER_SIZE <= 0) && !t_char_node[fd])
	{
		free (buffer);
		return (NULL);
	}
	buffer[r] = '\0';
	create_new_node(fd, buffer, r, &t_char_node[fd]);
	return (create_new_line(&t_char_node[fd]));
}
