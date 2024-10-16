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
	int fd;
	struct stat sb;
	char **str = NULL;

	fd = open("out3", O_RDONLY | O_APPEND | O_CREAT, 0000);
	if (stat("/out", &sb) == -1)
		return (printf("failed\n"));
	if (S_ISDIR(sb.st_mode))
		return (printf("IS DIRECTORY!!!\n"));
	if (access("out", W_OK) == -1)
		return (printf("NOPERMITS!\n"));
	else
		printf("Amsel\n");
	dup2(fd, 1);
	close(fd);
	printf("I am writing !");
	return (0);
}
