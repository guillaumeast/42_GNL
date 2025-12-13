/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 17:27:55 by gastesan          #+#    #+#             */
/*   Updated: 2025/12/13 20:25:41 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif

typedef struct s_str
{
	char	*data;
	size_t	len;
	size_t	cap;
}	t_str;

typedef struct s_buffer
{
	char	data[BUFFER_SIZE];
	ssize_t	len;
}	t_buffer;

typedef struct s_stash
{
	int			fd;
	t_buffer	buffer;
	void		*next;
}	t_stash;

char	*get_next_line(int fd);
ssize_t	get_nl_index(const t_buffer *buffer);
void	buffer_move(t_buffer *buffer, size_t index);
void	buffer_reset(t_buffer *buffer);
void	ft_strncat(t_str *dst, const t_buffer *src, size_t n);

#endif
