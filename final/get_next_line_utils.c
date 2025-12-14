/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 23:01:03 by gastesan          #+#    #+#             */
/*   Updated: 2025/12/14 01:19:56 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#define LINE_INITIAL_SIZE 128

ssize_t	get_index_n(const char *buff, char c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (buff[i] == c)
			return ((ssize_t)i);
		i++;
	}
	return (-1);
}

bool	line_add(t_line *dst, const t_buffer *src, size_t n)
{
	size_t	required_cap;
	size_t	new_cap;
	size_t	i;

	required_cap = dst->len + (size_t)src->len + 1;
	if (dst->cap < required_cap)
	{
		if (dst->cap == 0)
			new_cap = LINE_INITIAL_SIZE;
		else
			new_cap = dst->cap;
		while (new_cap < required_cap)
			new_cap *= 2;
		if (!line_realloc(dst, new_cap))
			return (false);
	}
	i = 0;
	while (i < n)
	{
		dst->data[dst->len + i] = src->data[i];
		i++;
	}
	dst->data[dst->len + i] = '\0';
	dst->len += n;
	return (true);
}

bool	line_realloc(t_line *line, size_t cap)
{
	char	*old_data;
	char	*new_data;
	size_t	len_to_copy;
	size_t	i;

	old_data = line->data;
	new_data = malloc(cap);
	if (!new_data)
		return (false);
	if (line->len < cap)
		len_to_copy = line->len;
	else
		len_to_copy = cap;
	i = 0;
	while (i < len_to_copy)
	{
		new_data[i] = line->data[i];
		i++;
	}
	new_data[i] = '\0';
	free(old_data);
	line->data = new_data;
	line->len = len_to_copy;
	line->cap = cap;
	return (true);
}

void	buffer_move(t_buffer *buffer, size_t index)
{
	ssize_t	i;
	ssize_t	j;

	i = 0;
	j = (ssize_t) index;
	while (j < buffer->len)
		buffer->data[i++] = buffer->data[j++];
	buffer->len = i;
	while (i < BUFFER_SIZE)
		buffer->data[i++] = '\0';
}

void	buffer_reset(t_buffer *buffer)
{
	size_t	i;

	i = 0;
	while (i < BUFFER_SIZE)
		buffer->data[i++] = '\0';
	buffer->len = 0;
}
