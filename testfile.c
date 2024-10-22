#include <stdio.h>
#include <string.h>
#include "executor.h"

// int main()
// {
// 	printf("helloWorld\n");
// 	return (0);
// }

void leaks(void)
{
	system("leaks a.out");
}

char*	generate_file_path(int id)
{
	char	*full_path;
	char	*nbr;

	nbr = ft_itoa(id);
	full_path = ft_strjoin(BASE_PATH, nbr);
	free (nbr);
	return (full_path);
}

int main()
{
	// char *line;
	// char *delimiter;
	int fd;
	char *file_path;

	atexit(leaks);
	file_path = generate_file_path(2);
	fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0640);
	if (fd == -1)
		return (free(file_path), printf("error\n"));
	// delimiter = strdup("eof");
	// while (1)
	// {
	// 	line = readline("> ");
	// 	if (strcmp(line, delimiter) == 0)
	// 	{
	// 		free (line);
	// 		break ;
	// 	}
	// 	else
	// 	{
	// 		ft_putstr_fd(line, fd);
	// 		ft_putstr_fd("\n", fd);
	// 	}
	// }
	free(file_path);
	if (close(fd) < 0)
		return (1);

	return (0);
}
