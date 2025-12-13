#ifndef GNL_H
# define GNL_H

# include <fcntl.h>		// open()
# include <unistd.h>	// read(), close()
# include <stdlib.h>	// malloc(), free()
# include <stdio.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 512
#endif

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
void	str_init(t_str *str);
ssize_t	get_nl_index(const t_buffer *buffer);
void	ft_strncat(t_str *dst, const t_buffer *src, size_t n);
void	buffer_move(t_buffer *buffer, size_t index);
void	buffer_reset(t_buffer *buffer);

#endif
