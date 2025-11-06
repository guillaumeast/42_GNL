#include <stdio.h>
#include "get_next_line.h"

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc > 2)
	{
		fprintf(stderr, "Usage for stdin parsing: ./a.out\n");
		fprintf(stderr, "Usage for file parsing:  ./a.out <filepath>\n");
		return (1);
	}
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		while (1)
		{
			line = get_next_line(fd);
			if (!line)
				break;
			printf("%s", line);
			fflush(stdout);
			free(line);
		}
		close(fd);
	}
	return (0);
}
