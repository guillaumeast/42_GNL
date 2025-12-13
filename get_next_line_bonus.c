/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:41:18 by gastesan          #+#    #+#             */
/*   Updated: 2025/12/13 20:22:04 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static t_buffer	*get_buffer(t_stash **stashs, int fd);
static t_stash	*stash_add(t_stash **stashs, int fd);
static void		stash_remove(t_stash **stashs, int fd);
static char		*parse_line(int fd, t_stash **stashs, t_buffer *b, t_str *res);

char	*get_next_line(int fd)
{
	static t_stash	*first_stash;
	t_buffer		*buffer;
	t_str			res;
	char			*ret;

	if (fd < 0)
		return (NULL);
	buffer = get_buffer(&first_stash, fd);
	if (!buffer)
		return (NULL);
	res.data = NULL;
	res.len = 0;
	res.cap = 0;
	return (ret = parse_line(fd, &first_stash, buffer, &res));
}

static t_buffer	*get_buffer(t_stash **stashs, int fd)
{
	t_stash	*stash;
	t_stash	*new_stash;

	stash = *stashs;
	while (stash)
	{
		if (stash->fd == fd)
			return (&stash->buffer);
		if (!stash->next)
			break ;
		stash = stash->next;
	}
	new_stash = stash_add(stashs, fd);
	if (!new_stash)
		return (NULL);
	return (&new_stash->buffer);
}

static t_stash	*stash_add(t_stash **stashs, int fd)
{
	t_stash	*new_stash;
	t_stash	*last_stash;

	new_stash = malloc(sizeof(t_stash));
	if (!new_stash)
		return (NULL);
	new_stash->fd = fd;
	new_stash->next = NULL;
	buffer_reset(&new_stash->buffer);
	if (!*stashs)
	{
		*stashs = new_stash;
		return (new_stash);
	}
	last_stash = *stashs;
	while (last_stash->next)
		last_stash = last_stash->next;
	last_stash->next = new_stash;
	return (new_stash);
}

static void	stash_remove(t_stash **stashs, int fd)
{
	t_stash	*stash;
	t_stash	*next;

	if (!stashs || !*stashs)
		return ;
	if ((*stashs)->fd == fd)
	{
		next = (*stashs)->next;
		free(*stashs);
		(*stashs) = next;
		return ;
	}
	stash = (*stashs);
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

static char	*parse_line(int fd, t_stash **stashs, t_buffer *b, t_str *res)
{
	ssize_t	nl_index;

	if (b->len <= 0)
		b->len = read(fd, b->data, BUFFER_SIZE);
	while (b->len > 0)
	{
		nl_index = get_nl_index(b);
		if (nl_index >= 0)
		{
			ft_strncat(res, b, (size_t)(nl_index + 1));
			buffer_move(b, (size_t)(nl_index + 1));
			return (res->data);
		}
		ft_strncat(res, b, (size_t)b->len);
		if (!res->data)
			return (stash_remove(stashs, fd), NULL);
		buffer_reset(b);
		b->len = read(fd, b->data, BUFFER_SIZE);
	}
	if (b->len == -1)
		return (free(res->data), stash_remove(stashs, fd), NULL);
	if (b->len == 0)
		stash_remove(stashs, fd);
	return (res->data);
}
