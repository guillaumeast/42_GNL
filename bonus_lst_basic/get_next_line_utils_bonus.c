/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:41:26 by gastesan          #+#    #+#             */
/*   Updated: 2025/12/13 20:31:34 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

#define STR_INITIAL_SIZE 128

static void	str_free(t_str *str);

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
	char	*new_data;
	size_t	i;
	size_t	j;

	new_data = malloc(dst->len + n + 1);
	if (!new_data)
		return (str_free(dst));
	i = 0;
	while (i < dst->len)
	{
		new_data[i] = dst->data[i];
		i++;
	}
	j = 0;
	while (j < n && src->data[j])
	{
		new_data[i + j] = src->data[j];
		j++;
	}
	new_data[i + j] = '\0';
	free(dst->data);
	dst->data = new_data;
	dst->len = i + j;
}

static void	str_free(t_str *str)
{
	if (str->data)
		free(str->data);
	str->data = NULL;
	str->len = 0;
}
