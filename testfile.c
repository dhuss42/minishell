#include <stdio.h>
#include <string.h>
#include "executor.h"

// int main()
// {
// 	printf("helloWorld\n");
// 	return (0);
// }

int main()
{
	char *line;
	char *delimiter;
	int fd;

	fd = open("temp", O_WRONLY | O_CREAT | O_TRUNC, 0640);
	if (fd == -1)
		return (printf("error\n"));
	delimiter = strdup("eof");
	while (1)
	{
		line = readline("> ");
		if (strcmp(line, delimiter) == 0)
		{
			free (line);
			break ;
		}
		else
		{
			ft_putstr_fd(line, fd);
			ft_putstr_fd("\n", fd);
		}
	}
	// fd = open("temp", O_RDONLY);
	// while (line = get_next_line(fd))
	// {
	// 	printf()
	// }

	return (0);
}
