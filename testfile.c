#include <stdio.h>
#include "executor.h"

// int main()
// {
// 	printf("helloWorld\n");
// 	return (0);
// }

int main()
{
	int fd;

	fd = open("out3", O_RDONLY | O_APPEND | O_CREAT, 0000);
	if (access("out3", W_OK) == -1)
		return (printf("NOPERMITS!\n"));
	else
		printf("Amsel\n");
	dup2(fd, 1);
	close(fd);
	printf("I am writing !");
	return (0);
}
