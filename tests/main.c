#include "get_next_line.h"
#include <stdio.h>

int	main(void)
{
	int	fd;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
	close(fd);
}
