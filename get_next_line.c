/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:41:18 by gastesan          #+#    #+#             */
/*   Updated: 2025/11/06 18:27:01 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	ssize_t		read_bytes;
	char		*res;
	size_t		res_len;
	ssize_t		nl_index;

	if (fd == -1)
		return (NULL);
	res = NULL;
	res_len = 0;
	read_bytes = ft_strnlen(buffer, BUFFER_SIZE);
	if (read_bytes == 0)
		read_bytes = read(fd, buffer, BUFFER_SIZE);
	while (read_bytes > 0)
	{
		nl_index = get_nl_index(buffer, read_bytes);
		if (nl_index >= 0)
		{
			res = ft_strncat(res, res_len, buffer, nl_index + 1);
			reset_buffer(buffer, nl_index);
			read_bytes -= nl_index + 1;
			return (res);
		}
		res = ft_strncat(res, res_len, buffer, read_bytes);
		res_len += (size_t) read_bytes;
		reset_buffer(buffer, nl_index);
		read_bytes = read(fd, buffer, BUFFER_SIZE);
	}
	if (read_bytes == -1)
	{
		if (res)
			free(res);
		return (NULL);
	}
	return (res);
}
