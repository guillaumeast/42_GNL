#ifndef GNL_H
# define GNL_H

# include <fcntl.h>		// open()
# include <unistd.h>	// read(), close()
# include <stdlib.h>	// malloc(), free()
# include <stdio.h>

char	*get_next_line(int fd);
size_t	ft_strnlen(char	*buffer, size_t n);
ssize_t	get_nl_index(const char *buffer, size_t n);
char	*ft_strncat(char *str, size_t str_len, char *buffer, size_t n);
void	reset_buffer(char *buffer, ssize_t nl_index);

#endif
