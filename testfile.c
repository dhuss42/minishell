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
	char str[] = "Hallo du ";

	fd = open("out3", O_WRONLY | O_CREAT| O_TRUNC, 0644);
	dup2(fd, 1);
	// write (fd, str, strlen(str));
	close(fd);
	printf("I am writing !");
	return (0);
}
