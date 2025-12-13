/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 23:31:54 by gastesan          #+#    #+#             */
/*   Updated: 2025/12/14 00:13:38 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_buffer	*get_buffer(t_stash **stashs_head, int fd);
static t_stash	*stash_add(t_stash **stashs_head, int fd);
static void		stash_remove(t_stash **stashs_head, int fd);
static char		*parse_line(int fd, t_buffer *b, t_line *res);

char	*get_next_line(int fd)
{
	static t_stash	*stashs_head;
	t_buffer		*buffer;
	t_line			res;
	char			*ret;

	if (fd < 0)
		return (NULL);
	buffer = get_buffer(&stashs_head, fd);
	if (!buffer)
		return (NULL);
	res.data = NULL;
	res.len = 0;
	res.cap = 0;
	ret = parse_line(fd, buffer, &res);
	if (!ret || buffer->len == 0)
		stash_remove(&stashs_head, fd);
	return (ret);
}

static t_buffer	*get_buffer(t_stash **stashs_head, int fd)
{
	t_stash	*stash;
	t_stash	*new_stash;

	stash = *stashs_head;
	while (stash)
	{
		if (stash->fd == fd)
			return (&stash->buffer);
		if (!stash->next)
			break ;
		stash = stash->next;
	}
	new_stash = stash_add(stashs_head, fd);
	if (!new_stash)
		return (NULL);
	return (&new_stash->buffer);
}

static t_stash	*stash_add(t_stash **stashs_head, int fd)
{
	t_stash	*new_stash;
	t_stash	*last_stash;

	new_stash = malloc(sizeof(t_stash));
	if (!new_stash)
		return (NULL);
	new_stash->fd = fd;
	new_stash->next = NULL;
	buffer_reset(&new_stash->buffer);
	if (!*stashs_head)
	{
		*stashs_head = new_stash;
		return (new_stash);
	}
	last_stash = *stashs_head;
	while (last_stash->next)
		last_stash = last_stash->next;
	last_stash->next = new_stash;
	return (new_stash);
}

static void	stash_remove(t_stash **stashs_head, int fd)
{
	t_stash	*stash;
	t_stash	*next;

	if (!stashs_head || !*stashs_head)
		return ;
	if ((*stashs_head)->fd == fd)
	{
		next = (*stashs_head)->next;
		free(*stashs_head);
		(*stashs_head) = next;
		return ;
	}
	stash = (*stashs_head);
	while (stash->next)
	{
		next = stash->next;
		if (next->fd == fd)
			break ;
		stash = next;
	}
	if (!next || next->fd != fd)
		return ;
	stash->next = next->next;
	free(next);
}

static char	*parse_line(int fd, t_buffer *b, t_line *res)
{
	ssize_t	nl_index;

	if (b->len <= 0)
		b->len = read(fd, b->data, BUFFER_SIZE);
	while (b->len > 0)
	{
		nl_index = get_index_n(b->data, '\n', (size_t)b->len);
		if (nl_index >= 0)
		{
			line_add(res, b, (size_t)(nl_index + 1));
			if (!res->data)
				return (NULL);
			buffer_move(b, (size_t)(nl_index + 1));
			return (res->data);
		}
		line_add(res, b, (size_t)b->len);
		if (!res->data)
			return (NULL);
		buffer_reset(b);
		b->len = read(fd, b->data, BUFFER_SIZE);
	}
	if (b->len == -1)
		return (free(res->data), NULL);
	return (res->data);
}
