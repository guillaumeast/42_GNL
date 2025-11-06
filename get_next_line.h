#ifndef GNL_H
# define GNL_H

# include <fcntl.h>		// open()
# include <unistd.h>	// read(), close()
# include <stdlib.h>	// malloc(), free()
# include <stdio.h>

typedef int t_bool;
# define TRUE 1
# define FALSE 0

typedef struct s_str
{
	char	*data;
	size_t	len;
}	t_str;

typedef struct s_buffer
{
	char	data[BUFFER_SIZE];
	ssize_t	len;
}	t_buffer;

char	*get_next_line(int fd);
ssize_t	get_nl_index(const t_buffer *buffer);
void	ft_strncat(t_str *dst, const t_buffer *src, const size_t n);
void	move_buffer(t_buffer *buffer, const size_t index);
void	reset_buffer(t_buffer *buffer);

#endif
