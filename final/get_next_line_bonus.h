/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 22:59:45 by gastesan          #+#    #+#             */
/*   Updated: 2025/12/13 23:44:51 by gastesan         ###   ########.fr       */
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
#  define BUFFER_SIZE 128
# endif

typedef struct s_line
{
	char	*data;
	size_t	len;
	size_t	cap;
}	t_line;

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
ssize_t	get_index_n(const char *buff, char c, size_t n);
bool	line_add(t_line *dst, const t_buffer *src, size_t n);
bool	line_realloc(t_line *line, size_t cap);
void	buffer_move(t_buffer *buffer, size_t index);
void	buffer_reset(t_buffer *buffer);

#endif
