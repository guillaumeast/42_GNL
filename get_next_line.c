/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:41:18 by gastesan          #+#    #+#             */
/*   Updated: 2025/11/06 20:23:28 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "get_next_line.h"

static void init_str(t_str *str)
{
	str->data = NULL;
	str->len = 0;
}

char	*get_next_line(int fd)
{
	static t_buffer	buffer;
	t_str			res;
	ssize_t			nl_index;

	if (fd == -1)
		return (NULL);
	init_str(&res);
	if (buffer.len == 0)
		buffer.len = read(fd, buffer.data, BUFFER_SIZE);
	while (buffer.len > 0)
	{
		nl_index = get_nl_index(&buffer);
		if (nl_index >= 0)
		{
			ft_strncat(&res, &buffer, (size_t)(nl_index + 1));
			move_buffer(&buffer, (size_t)(nl_index + 1));
			return (res.data);
		}
		ft_strncat(&res, &buffer, (size_t)buffer.len);
		if (!res.data)
			return (NULL);
		reset_buffer(&buffer);
		buffer.len = read(fd, buffer.data, BUFFER_SIZE);
	}
	if (buffer.len == -1)
	{
		free(res.data);
		return (NULL);
	}
	return (res.data);
}
