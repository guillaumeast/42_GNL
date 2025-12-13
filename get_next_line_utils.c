/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:41:26 by gastesan          #+#    #+#             */
/*   Updated: 2025/12/13 17:27:15 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#define STR_INITIAL_SIZE 128

static bool	str_grow(t_str *str, size_t required_cap);
static void	str_free(t_str *str);

void	str_init(t_str *str)
{
	str->data = NULL;
	str->len = 0;
	str->cap = 0;
}

void	ft_strncat(t_str *dst, const t_buffer *src, size_t n)
{
	size_t	i;

	if (!str_grow(dst, dst->len + n + 1))
		return (str_free(dst));
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

static void	str_free(t_str *str)
{
	if (str->data)
		free(str->data);
	str->data = NULL;
	str->len = 0;
}
