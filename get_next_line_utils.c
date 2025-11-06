/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:41:26 by gastesan          #+#    #+#             */
/*   Updated: 2025/11/06 18:04:58 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strnlen(char	*buffer, size_t n)
{
	size_t	len;

	len = 0;
	while (len < n && buffer[len])
		len++;
	return (len);
}

ssize_t	get_nl_index(const char *buffer, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (buffer[i] == '\n')
			return ((ssize_t) i);
		i++;
	}
	return (-1);
}

char	*ft_strncat(char *str, size_t str_len, char *buffer, size_t n)
{
	char	*res;
	size_t	i;
	size_t	j;

	res = malloc(str_len + n + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < str_len)
	{
		res[i] = str[i];
		i++;
	}
	j = 0;
	while (j < n)
	{
		res[i + j] = buffer[j];
		j++;
	}
	res[i + j] = '\0';
	free(str);
	return (res);
}

void	reset_buffer(char *buffer, ssize_t nl_index)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = (size_t) (nl_index + 1);
	while (j < BUFFER_SIZE)
		buffer[i++] = buffer[j++];
	while (i < BUFFER_SIZE)
		buffer[i++] = '\0';
}
