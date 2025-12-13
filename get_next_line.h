#ifndef GNL_H
# define GNL_H

# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 512
#endif

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

char	*get_next_line(int fd);
void	str_init(t_str *str);
void	ft_strncat(t_str *dst, const t_buffer *src, size_t n);

#endif
