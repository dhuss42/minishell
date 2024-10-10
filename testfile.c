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

	fd = open("out3", O_WRONLY | O_APPEND, 0644);
	dup2(fd, 1);
	close(fd);
	printf("I am writing !");
	return (0);
}
