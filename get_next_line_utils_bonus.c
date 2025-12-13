/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:41:26 by gastesan          #+#    #+#             */
/*   Updated: 2025/12/13 19:08:44 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#define STR_INITIAL_SIZE 128

static bool	str_grow(t_str *str, size_t required_cap);

ssize_t	get_nl_index(const t_buffer *buffer)
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

void	ft_strncat(t_str *dst, const t_buffer *src, size_t n)
{
	size_t	i;

	if (!str_grow(dst, dst->len + n + 1))
	{
		if (dst->data)
			free(dst->data);
		dst->data = NULL;
		dst->len = 0;
		return ;
	}
	i = 0;
	while (i < n)
	{
		dst->data[dst->len + i] = src->data[i];
		i++;
	}
	dst->data[dst->len + i] = '\0';
	dst->len += n;
}

static bool	str_grow(t_str *str, size_t required_cap)
{
	size_t	new_cap;
	char	*new_data;
	size_t	i;

	if (str->cap >= required_cap)
		return (true);
	if (str->cap == 0)
		new_cap = STR_INITIAL_SIZE;
	else
		new_cap = str->cap;
	while (new_cap < required_cap)
		new_cap *= 2;
	new_data = malloc(new_cap);
	if (!new_data)
		return (false);
	i = 0;
	while (i < str->len)
	{
		new_data[i] = str->data[i];
		i++;
	}
	free(str->data);
	str->data = new_data;
	str->cap = new_cap;
	return (true);
}
