/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:41:18 by gastesan          #+#    #+#             */
/*   Updated: 2025/12/13 21:00:05 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*parse_line(int fd, t_buffer *buffer, t_str *res);
static ssize_t	get_nl_index(const t_buffer *buffer);

char	*get_next_line(int fd)
{
	static t_buffer	buffer;
	t_str			res;

	if (fd < 0)
		return (NULL);
	str_init(&res);
	return (parse_line(fd, &buffer, &res));
}

static char	*parse_line(int fd, t_buffer *buffer, t_str *res)
{
	ssize_t	nl_index;

	if (buffer->len <= 0)
		buffer->len = read(fd, buffer->data, BUFFER_SIZE);
	while (buffer->len > 0)
	{
		nl_index = get_nl_index(buffer);
		if (nl_index >= 0)
		{
			ft_strncat(res, buffer, (size_t)(nl_index + 1));
			buffer_move(buffer, (size_t)(nl_index + 1));
			return (res->data);
		}
		ft_strncat(res, buffer, (size_t)buffer->len);
		if (!res->data)
			return (NULL);
		buffer_reset(buffer);
		buffer->len = read(fd, buffer->data, BUFFER_SIZE);
	}
	if (buffer->len == -1)
	{
		free(res->data);
		return (NULL);
	}
	return (res->data);
}

static ssize_t	get_nl_index(const t_buffer *buffer)
{
	ssize_t	i;

	i = 0;
	while (i < buffer->len)
	{
		if (buffer->data[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
